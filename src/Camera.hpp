#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Camera {
public:
    Camera();

    void reset();
    void processKeyboard(GLFWwindow *window, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);
    void processScroll(float yOffset);

    glm::mat4 viewMatrix() const;
    float fov() const { return m_fov; }
    glm::vec3 position() const { return m_position; }

private:
    void adjustDistance(float amount);
    void updateVectors();

    glm::vec3 m_position{};
    glm::vec3 m_front{};
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp{0.0f, 1.0f, 0.0f};
    glm::vec3 m_target{};

    float m_yaw = 90.0f;
    float m_pitch = 42.0f;
    float m_distance = 8.2f;
    float m_fov = 38.0f;
    float m_orbitSpeed = 70.0f;
    float m_zoomSpeed = 4.0f;
    float m_mouseSensitivity = 0.18f;
};
