#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BlackHole.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "Grid.hpp"
#include "ParticleSystem.hpp"
#include "Shader.hpp"

#include <exception>
#include <iostream>
#include <string>

namespace {
constexpr int InitialWidth = 1280;
constexpr int InitialHeight = 720;
constexpr size_t NumParticles = 200000;
constexpr float EventHorizonRadius = 1.0f;
constexpr float GrainStrength = 0.25f;
constexpr float BloomStrength = 0.35f;
constexpr float VignetteStrength = 0.65f;
constexpr float PostContrast = 1.25f;
constexpr float ParticleSizeScale = 1.0f;

Camera *g_camera = nullptr;
bool g_firstMouse = true;
bool g_cursorInside = false;
bool g_mouseLookActive = false;
float g_lastMouseX = InitialWidth * 0.5f;
float g_lastMouseY = InitialHeight * 0.5f;

std::string shaderPath(const std::string &file)
{
    return std::string(BLACKHOLE_SHADER_DIR) + "/" + file;
}

void framebufferSizeCallback(GLFWwindow *, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *, double xpos, double ypos)
{
    if (!g_camera || !g_cursorInside || !g_mouseLookActive) {
        g_firstMouse = true;
        return;
    }

    const float x = static_cast<float>(xpos);
    const float y = static_cast<float>(ypos);

    if (g_firstMouse) {
        g_lastMouseX = x;
        g_lastMouseY = y;
        g_firstMouse = false;
    }

    const float xOffset = x - g_lastMouseX;
    const float yOffset = g_lastMouseY - y;
    g_lastMouseX = x;
    g_lastMouseY = y;

    g_camera->processMouseMovement(xOffset, yOffset);
}

void cursorEnterCallback(GLFWwindow *, int entered)
{
    g_cursorInside = entered == GLFW_TRUE;
    if (!g_cursorInside) {
        g_mouseLookActive = false;
        g_firstMouse = true;
    }
}

void mouseButtonCallback(GLFWwindow *, int button, int action, int)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT) {
        return;
    }

    if (action == GLFW_PRESS && g_cursorInside) {
        g_mouseLookActive = true;
        g_firstMouse = true;
    } else if (action == GLFW_RELEASE) {
        g_mouseLookActive = false;
        g_firstMouse = true;
    }
}

void scrollCallback(GLFWwindow *, double, double yoffset)
{
    if (g_camera && g_cursorInside) {
        g_camera->processScroll(static_cast<float>(yoffset));
    }
}

bool consumePress(GLFWwindow *window, int key, bool &wasPressed)
{
    const bool pressed = glfwGetKey(window, key) == GLFW_PRESS;
    const bool triggered = pressed && !wasPressed;
    wasPressed = pressed;
    return triggered;
}

glm::vec2 projectOriginToScreen(const glm::mat4 &projection, const glm::mat4 &view)
{
    const glm::vec4 clip = projection * view * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    if (clip.w <= 0.0001f) {
        return glm::vec2(0.5f, 0.5f);
    }
    const glm::vec3 ndc = glm::vec3(clip) / clip.w;
    return glm::vec2(ndc.x * 0.5f + 0.5f, ndc.y * 0.5f + 0.5f);
}
}

int main()
{
    try {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW.\n";
            return 1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(
            InitialWidth,
            InitialHeight,
            "blackhole_mono_particles",
            nullptr,
            nullptr
        );

        if (!window) {
            glfwTerminate();
            std::cerr << "Failed to create GLFW window.\n";
            return 1;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glfwDestroyWindow(window);
            glfwTerminate();
            std::cerr << "Failed to load OpenGL functions with GLAD.\n";
            return 1;
        }

        glViewport(0, 0, InitialWidth, InitialHeight);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetCursorEnterCallback(window, cursorEnterCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        Camera camera;
        g_camera = &camera;

        Shader particleShader(shaderPath("particle.vert"), shaderPath("particle.frag"));
        Shader blackHoleShader(shaderPath("blackhole.vert"), shaderPath("blackhole.frag"));
        Shader gridShader(shaderPath("grid.vert"), shaderPath("grid.frag"));
        Shader postShader(shaderPath("screen.vert"), shaderPath("post.frag"));

        ParticleSystem particles(NumParticles);
        Grid grid(10.0f, 80);
        BlackHole blackHole(EventHorizonRadius);
        Framebuffer framebuffer(InitialWidth, InitialHeight);

        bool paused = false;
        bool showGrid = true;
        bool enablePost = true;
        bool enableGrain = true;

        bool spacePressed = false;
        bool rPressed = false;
        bool gPressed = false;
        bool pPressed = false;
        bool nPressed = false;

        float lastTime = static_cast<float>(glfwGetTime());
        float simulationTime = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            const float currentTime = static_cast<float>(glfwGetTime());
            const float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            if (consumePress(window, GLFW_KEY_SPACE, spacePressed)) {
                paused = !paused;
            }
            if (consumePress(window, GLFW_KEY_R, rPressed)) {
                camera.reset();
                g_firstMouse = true;
                g_mouseLookActive = false;
            }
            if (consumePress(window, GLFW_KEY_G, gPressed)) {
                showGrid = !showGrid;
            }
            if (consumePress(window, GLFW_KEY_P, pPressed)) {
                enablePost = !enablePost;
            }
            if (consumePress(window, GLFW_KEY_N, nPressed)) {
                enableGrain = !enableGrain;
            }

            camera.processKeyboard(window, deltaTime);

            int width = 0;
            int height = 0;
            glfwGetFramebufferSize(window, &width, &height);
            if (width <= 0 || height <= 0) {
                glfwPollEvents();
                continue;
            }
            framebuffer.resize(width, height);

            const glm::mat4 model(1.0f);
            const glm::mat4 view = camera.viewMatrix();
            const glm::mat4 projection = glm::perspective(
                glm::radians(camera.fov()),
                static_cast<float>(width) / static_cast<float>(height),
                0.1f,
                100.0f
            );

            if (!paused) {
                simulationTime += deltaTime;
            }

            framebuffer.bind();
            glViewport(0, 0, width, height);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (showGrid) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDepthMask(GL_FALSE);

                gridShader.use();
                gridShader.setMat4("model", model);
                gridShader.setMat4("view", view);
                gridShader.setMat4("projection", projection);
                gridShader.setFloat("time", currentTime);
                grid.render(gridShader);

                glDepthMask(GL_TRUE);
                glDisable(GL_BLEND);
            }

            blackHoleShader.use();
            blackHoleShader.setMat4("model", model);
            blackHoleShader.setMat4("view", view);
            blackHoleShader.setMat4("projection", projection);
            blackHole.render(blackHoleShader);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthMask(GL_FALSE);

            particleShader.use();
            particleShader.setMat4("model", model);
            particleShader.setMat4("view", view);
            particleShader.setMat4("projection", projection);
            particleShader.setFloat("simulationTime", simulationTime);
            particleShader.setFloat("particleSizeScale", ParticleSizeScale);
            particleShader.setFloat("grainStrength", enableGrain ? GrainStrength : 0.0f);
            particleShader.setFloat("time", currentTime);
            particles.render(particleShader);

            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);

            Framebuffer::bindDefault();
            glViewport(0, 0, width, height);
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);

            postShader.use();
            postShader.setInt("screenTexture", 0);
            postShader.setBool("enablePost", enablePost);
            postShader.setBool("enableGrain", enableGrain);
            postShader.setFloat("time", currentTime);
            postShader.setFloat("grainStrength", GrainStrength);
            postShader.setFloat("bloomStrength", BloomStrength);
            postShader.setFloat("vignetteStrength", VignetteStrength);
            postShader.setFloat("contrast", PostContrast);
            postShader.setVec2("resolution", static_cast<float>(width), static_cast<float>(height));

            const glm::vec2 blackHoleScreen = projectOriginToScreen(projection, view);
            postShader.setVec2("blackHoleScreenPos", blackHoleScreen.x, blackHoleScreen.y);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, framebuffer.texture());
            framebuffer.renderQuad();

            glEnable(GL_DEPTH_TEST);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        g_camera = nullptr;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        glfwTerminate();
        return 1;
    }
}
