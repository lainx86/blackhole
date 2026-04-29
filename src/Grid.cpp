#include "Grid.hpp"

#include "Shader.hpp"

#include <cmath>

Grid::Grid(float extent, int divisions)
{
    generate(extent, divisions);
}

Grid::~Grid()
{
    destroy();
}

void Grid::generate(float extent, int divisions)
{
    destroy();
    m_vertices.clear();

    const float step = (extent * 2.0f) / static_cast<float>(divisions);
    for (int line = 0; line <= divisions; ++line) {
        const float fixed = -extent + static_cast<float>(line) * step;
        for (int segment = 0; segment < divisions; ++segment) {
            const float a = -extent + static_cast<float>(segment) * step;
            const float b = a + step;

            m_vertices.push_back(point(a, fixed));
            m_vertices.push_back(point(b, fixed));

            m_vertices.push_back(point(fixed, a));
            m_vertices.push_back(point(fixed, b));
        }
    }

    upload();
}

void Grid::render(const Shader &shader) const
{
    shader.use();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_vertices.size()));
    glBindVertexArray(0);
}

glm::vec3 Grid::point(float x, float z)
{
    const float r = std::sqrt(x * x + z * z);
    const float strength = 1.25f;
    const float softness = 0.55f;
    float depression = -strength / (r * r + softness);
    if (r < 1.1f) {
        depression *= r / 1.1f;
    }
    return glm::vec3(x, depression, z);
}

void Grid::upload()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(m_vertices.size() * sizeof(glm::vec3)),
        m_vertices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Grid::destroy()
{
    if (m_vbo != 0) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}
