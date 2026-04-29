#include "BlackHole.hpp"

#include "Shader.hpp"

#include <cmath>

namespace {
constexpr float Pi = 3.14159265358979323846f;
}

BlackHole::BlackHole(float radius)
    : m_radius(radius)
{
    generateMesh();
}

BlackHole::~BlackHole()
{
    destroy();
}

void BlackHole::render(const Shader &shader) const
{
    shader.use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void BlackHole::generateMesh()
{
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;

    constexpr int stacks = 40;
    constexpr int slices = 64;

    for (int stack = 0; stack <= stacks; ++stack) {
        const float v = static_cast<float>(stack) / static_cast<float>(stacks);
        const float phi = v * Pi;
        const float y = std::cos(phi);
        const float ringRadius = std::sin(phi);

        for (int slice = 0; slice <= slices; ++slice) {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = u * 2.0f * Pi;
            const float x = ringRadius * std::cos(theta);
            const float z = ringRadius * std::sin(theta);
            vertices.emplace_back(x * m_radius, y * m_radius, z * m_radius);
        }
    }

    for (int stack = 0; stack < stacks; ++stack) {
        for (int slice = 0; slice < slices; ++slice) {
            const int first = stack * (slices + 1) + slice;
            const int second = first + slices + 1;

            indices.push_back(static_cast<GLuint>(first));
            indices.push_back(static_cast<GLuint>(second));
            indices.push_back(static_cast<GLuint>(first + 1));

            indices.push_back(static_cast<GLuint>(second));
            indices.push_back(static_cast<GLuint>(second + 1));
            indices.push_back(static_cast<GLuint>(first + 1));
        }
    }

    m_indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(glm::vec3)),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)),
        indices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

    glBindVertexArray(0);
}

void BlackHole::destroy()
{
    if (m_ebo != 0) {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
    if (m_vbo != 0) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}
