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
uniform vec3 cameraPosition;
uniform float dopplerStrength;
uniform float backArcLift;

out float vBrightness;

void main()
{
    float angle = aAngle + aAngularVelocity * simulationTime;
    float radialBreath = sin(simulationTime * 0.45 + aNoiseSeed) * 0.018;
    float spiralPulse = sin(angle * 3.0 + aRadius * 2.7 + simulationTime * 0.35) * 0.028;
    float radius = clamp(aRadius + radialBreath + spiralPulse, 1.4, 8.0);
    float verticalJitter = sin(simulationTime * 1.4 + aNoiseSeed + angle * 2.0) * 0.18 * (0.12 + radius * 0.015);

    vec3 cameraFlat = vec3(cameraPosition.x, 0.0, cameraPosition.z);
    cameraFlat /= max(length(cameraFlat), 0.0001);
    vec3 radialDir = vec3(cos(angle), 0.0, sin(angle));
    float frontness = dot(radialDir, cameraFlat);
    float backSide = 1.0 - smoothstep(-0.30, 0.12, frontness);
    float radialLift = pow(clamp(1.0 - smoothstep(1.4, 8.0, radius), 0.0, 1.0), 2.0);

    vec3 pos = vec3(cos(angle) * radius, aHeightOffset + verticalJitter, sin(angle) * radius);
    pos.y += backSide * radialLift * 0.28;

    vec4 worldPos = model * vec4(pos, 1.0);
    vec4 viewPos = view * worldPos;
    float dist = max(length(viewPos.xyz), 0.001);
    float flicker = 0.94 + 0.06 * sin(simulationTime * 2.0 + aNoiseSeed);

    vec3 tangent = normalize(vec3(-sin(angle), 0.0, cos(angle)));
    vec3 toCamera = normalize(cameraPosition - worldPos.xyz);
    float approach = dot(tangent, toCamera);
    float doppler = clamp(1.0 + dopplerStrength * approach, 0.62, 1.38);
    float lensedBackBoost = 1.0 + backSide * radialLift * 0.16;

    vec4 clipPos = projection * viewPos;
    clipPos.y += clipPos.w * backSide * radialLift * backArcLift;

    gl_Position = clipPos;
    gl_PointSize = clamp(aSize * particleSizeScale * (18.0 / dist), 1.0, 4.0);
    vBrightness = clamp(aBrightness * flicker * doppler * lensedBackBoost, 0.01, 0.86);
}
