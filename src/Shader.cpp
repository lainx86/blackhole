#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    load(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    destroy();
}

Shader::Shader(Shader &&other) noexcept
    : m_id(other.m_id)
{
    other.m_id = 0;
}

Shader &Shader::operator=(Shader &&other) noexcept
{
    if (this != &other) {
        destroy();
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void Shader::load(const std::string &vertexPath, const std::string &fragmentPath)
{
    destroy();

    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);

    const GLuint vertex = compile(GL_VERTEX_SHADER, vertexSource, vertexPath);
    const GLuint fragment = compile(GL_FRAGMENT_SHADER, fragmentSource, fragmentPath);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> log(static_cast<size_t>(logLength) + 1);
        glGetProgramInfoLog(m_id, logLength, nullptr, log.data());
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        throw std::runtime_error("Shader link failed:\n" + std::string(log.data()));
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(uniformLocation(name), value ? 1 : 0);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(uniformLocation(name), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(uniformLocation(name), value);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(uniformLocation(name), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(uniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::readFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

GLuint Shader::compile(GLenum type, const std::string &source, const std::string &path)
{
    const GLuint shader = glCreateShader(type);
    const char *sourcePtr = source.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> log(static_cast<size_t>(logLength) + 1);
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        glDeleteShader(shader);
        throw std::runtime_error("Shader compile failed for " + path + ":\n" + std::string(log.data()));
    }

    return shader;
}

GLint Shader::uniformLocation(const std::string &name) const
{
    return glGetUniformLocation(m_id, name.c_str());
}

void Shader::destroy()
{
    if (m_id != 0) {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}
