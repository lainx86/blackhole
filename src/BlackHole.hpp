#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Shader;

class BlackHole {
public:
    explicit BlackHole(float radius = 1.0f);
    ~BlackHole();

    BlackHole(const BlackHole &) = delete;
    BlackHole &operator=(const BlackHole &) = delete;

    void render(const Shader &shader) const;
    float radius() const { return m_radius; }

private:
    float m_radius = 1.0f;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;
    GLsizei m_indexCount = 0;

    void generateMesh();
    void destroy();
};
