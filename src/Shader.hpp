#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader {
public:
    Shader() = default;
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&other) noexcept;
    Shader &operator=(Shader &&other) noexcept;

    void load(const std::string &vertexPath, const std::string &fragmentPath);
    void use() const;

    GLuint id() const { return m_id; }

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;

private:
    GLuint m_id = 0;

    static std::string readFile(const std::string &path);
    static GLuint compile(GLenum type, const std::string &source, const std::string &path);
    GLint uniformLocation(const std::string &name) const;
    void destroy();
};
