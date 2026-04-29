#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Shader;

class Grid {
public:
    Grid() = default;
    Grid(float extent, int divisions);
    ~Grid();

    Grid(const Grid &) = delete;
    Grid &operator=(const Grid &) = delete;

    void generate(float extent, int divisions);
    void render(const Shader &shader) const;

private:
    std::vector<glm::vec3> m_vertices;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;

    static glm::vec3 point(float x, float z);
    void upload();
    void destroy();
};
