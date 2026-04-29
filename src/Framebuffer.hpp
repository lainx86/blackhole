#pragma once

#include <glad/glad.h>

class Framebuffer {
public:
    Framebuffer() = default;
    Framebuffer(int width, int height);
    ~Framebuffer();

    Framebuffer(const Framebuffer &) = delete;
    Framebuffer &operator=(const Framebuffer &) = delete;

    void create(int width, int height);
    void resize(int width, int height);
    void bind() const;
    static void bindDefault();
    void renderQuad() const;

    GLuint texture() const { return m_colorTexture; }
    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    GLuint m_fbo = 0;
    GLuint m_colorTexture = 0;
    GLuint m_rbo = 0;
    GLuint m_quadVao = 0;
    GLuint m_quadVbo = 0;
    int m_width = 0;
    int m_height = 0;

    void createQuad();
    void destroyFramebuffer();
    void destroyAll();
};
