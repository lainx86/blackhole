#version 330 core

layout(location = 0) in float aRadius;
layout(location = 1) in float aAngle;
layout(location = 2) in float aSize;
layout(location = 3) in float aBrightness;
layout(location = 4) in float aAngularVelocity;
layout(location = 5) in float aNoiseSeed;
layout(location = 6) in float aHeightOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float simulationTime;
uniform float particleSizeScale;

out float vBrightness;

void main()
{
    float angle = aAngle + aAngularVelocity * simulationTime;
    float radialBreath = sin(simulationTime * 0.45 + aNoiseSeed) * 0.018;
    float spiralPulse = sin(angle * 3.0 + aRadius * 2.7 + simulationTime * 0.35) * 0.028;
    float radius = clamp(aRadius + radialBreath + spiralPulse, 1.4, 8.0);
    float verticalJitter = sin(simulationTime * 1.4 + aNoiseSeed + angle * 2.0) * 0.18 * (0.12 + radius * 0.015);

    vec3 pos = vec3(cos(angle) * radius, aHeightOffset + verticalJitter, sin(angle) * radius);
    vec4 worldPos = model * vec4(pos, 1.0);
    vec4 viewPos = view * worldPos;
    float dist = max(length(viewPos.xyz), 0.001);
    float flicker = 0.92 + 0.08 * sin(simulationTime * 2.0 + aNoiseSeed);

    gl_Position = projection * viewPos;
    gl_PointSize = clamp(aSize * particleSizeScale * (20.0 / dist), 1.0, 5.0);
    vBrightness = clamp(aBrightness * flicker, 0.02, 1.0);
}
