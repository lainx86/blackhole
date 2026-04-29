#include "ParticleSystem.hpp"

#include "Shader.hpp"

#include <glm/common.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

namespace {
constexpr float TwoPi = 6.28318530717958647692f;

float smoothstep(float edge0, float edge1, float value)
{
    const float t = glm::clamp((value - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
}

ParticleSystem::ParticleSystem(size_t count)
{
    initialize(count);
}

ParticleSystem::~ParticleSystem()
{
    destroy();
}

void ParticleSystem::initialize(size_t count)
{
    destroy();

    m_particles.clear();
    m_gpuParticles.clear();
    m_particles.reserve(count);
    m_gpuParticles.reserve(count);

    std::mt19937 rng(1337u);
    std::uniform_real_distribution<float> rand01(0.0f, 1.0f);

    for (size_t i = 0; i < count; ++i) {
        const float innerSquared = InnerRadius * InnerRadius;
        const float outerSquared = OuterRadius * OuterRadius;
        float radius = std::sqrt(innerSquared + rand01(rng) * (outerSquared - innerSquared));
        float angle = rand01(rng) * TwoPi;

        const float clump = std::sin(angle * 5.0f + radius * 2.0f) * 0.08f;
        const float spiral = std::sin(angle * 2.0f + radius * 3.5f) * 0.14f;
        radius += clump + spiral + (rand01(rng) - 0.5f) * 0.08f;
        radius = glm::clamp(radius, InnerRadius, OuterRadius);

        const float thickness = DiskThickness * (0.45f + 0.55f * radius / OuterRadius);
        const float y = (rand01(rng) - 0.5f) * thickness;

        const float innerHeat = 1.0f - smoothstep(InnerRadius, OuterRadius * 0.82f, radius);
        const float innerGate = smoothstep(InnerRadius * 0.92f, InnerRadius * 1.45f, radius);
        const float outerFade = 1.0f - smoothstep(OuterRadius * 0.82f, OuterRadius, radius);
        const float densityPattern = 0.5f + 0.5f * std::sin(angle * 5.0f + radius * 2.4f);
        const float filament = 0.5f + 0.5f * std::sin(angle * 2.0f - radius * 3.0f);
        const float gasPattern = 0.58f + 0.28f * densityPattern + 0.14f * filament;
        const float noise = 0.42f + 0.58f * rand01(rng);
        const float brightness = glm::clamp(
            (0.035f + innerHeat * 0.42f * noise * gasPattern) * innerGate * outerFade + 0.016f,
            0.012f,
            0.58f
        );

        const float sizeRoll = rand01(rng);
        float size = 0.0f;
        if (sizeRoll < 0.78f) {
            size = MinParticleSize + rand01(rng) * 0.55f;
        } else if (sizeRoll < 0.97f) {
            size = 1.25f + rand01(rng) * 0.55f;
        } else {
            size = 1.80f + rand01(rng) * (MaxParticleSize - 1.80f);
        }
        size = glm::clamp(size, MinParticleSize, MaxParticleSize);

        Particle particle;
        particle.radius = radius;
        particle.angle = angle;
        particle.size = size;
        particle.brightness = brightness;
        particle.angularVelocity = BaseOrbitSpeed / std::pow(glm::max(radius, 0.15f), 1.5f);
        particle.noiseSeed = rand01(rng) * 1000.0f;
        particle.heightOffset = y;
        particle.position = glm::vec3(std::cos(angle) * radius, y, std::sin(angle) * radius);

        m_particles.push_back(particle);
        m_gpuParticles.push_back({
            particle.radius,
            particle.angle,
            particle.size,
            particle.brightness,
            particle.angularVelocity,
            particle.noiseSeed,
            particle.heightOffset
        });
    }

    uploadAll();
}

void ParticleSystem::render(const Shader &shader) const
{
    shader.use();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(m_gpuParticles.size()));
    glBindVertexArray(0);
}

void ParticleSystem::uploadAll()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(m_gpuParticles.size() * sizeof(ParticleGpu)),
        m_gpuParticles.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, radius)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, angle)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, size)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, brightness)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, angularVelocity)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, noiseSeed)));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpu), reinterpret_cast<void *>(offsetof(ParticleGpu, heightOffset)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleSystem::destroy()
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
