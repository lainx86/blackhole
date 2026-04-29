#include "Camera.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>

Camera::Camera()
{
    reset();
}

void Camera::reset()
{
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw = 90.0f;
    m_pitch = 42.0f;
    m_distance = 8.2f;
    m_fov = 38.0f;
    m_orbitSpeed = 70.0f;
    m_zoomSpeed = 4.0f;
    m_mouseSensitivity = 0.18f;
    updateVectors();
}

void Camera::processKeyboard(GLFWwindow *window, float deltaTime)
{
    const float orbitStep = m_orbitSpeed * deltaTime;
    const float zoomStep = m_zoomSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        adjustDistance(-zoomStep);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        adjustDistance(zoomStep);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_yaw += orbitStep;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_yaw -= orbitStep;
    }

    updateVectors();
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    m_yaw -= xOffset * m_mouseSensitivity;
    m_pitch += yOffset * m_mouseSensitivity;
    m_pitch = std::clamp(m_pitch, -80.0f, 80.0f);
    updateVectors();
}

void Camera::processScroll(float yOffset)
{
    adjustDistance(-yOffset * m_zoomSpeed * 0.5f);
    updateVectors();
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_target, m_up);
}

void Camera::adjustDistance(float amount)
{
    m_distance = std::clamp(m_distance + amount, 2.0f, 25.0f);
}

void Camera::updateVectors()
{
    const float yawRadians = glm::radians(m_yaw);
    const float pitchRadians = glm::radians(m_pitch);

    glm::vec3 offset;
    offset.x = std::cos(pitchRadians) * std::cos(yawRadians) * m_distance;
    offset.y = std::sin(pitchRadians) * m_distance;
    offset.z = std::cos(pitchRadians) * std::sin(yawRadians) * m_distance;

    m_position = m_target + offset;
    m_front = glm::normalize(m_target - m_position);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
