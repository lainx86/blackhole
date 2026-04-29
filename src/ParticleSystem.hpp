#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <vector>

struct Particle {
    glm::vec3 position;
    float radius;
    float angle;
    float size;
    float brightness;
    float angularVelocity;
    float noiseSeed;
    float heightOffset;
};

struct ParticleGpu {
    float radius;
    float angle;
    float size;
    float brightness;
    float angularVelocity;
    float noiseSeed;
    float heightOffset;
};

class Shader;

class ParticleSystem {
public:
    static constexpr float InnerRadius = 1.4f;
    static constexpr float OuterRadius = 8.0f;
    static constexpr float DiskThickness = 0.18f;
    static constexpr float MinParticleSize = 0.75f;
    static constexpr float MaxParticleSize = 2.8f;
    static constexpr float BaseOrbitSpeed = 2.2f;

    ParticleSystem() = default;
    ParticleSystem(size_t count);
    ~ParticleSystem();

    ParticleSystem(const ParticleSystem &) = delete;
    ParticleSystem &operator=(const ParticleSystem &) = delete;

    void initialize(size_t count);
    void render(const Shader &shader) const;

    size_t count() const { return m_gpuParticles.size(); }

private:
    std::vector<Particle> m_particles;
    std::vector<ParticleGpu> m_gpuParticles;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;

    void uploadAll();
    void destroy();
};
