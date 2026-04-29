#version 330 core

in vec2 TexCoord;

uniform sampler2D screenTexture;
uniform bool enablePost;
uniform bool enableGrain;
uniform vec2 resolution;
uniform vec2 blackHoleScreenPos;
uniform float time;
uniform float grainStrength;
uniform float bloomStrength;
uniform float vignetteStrength;
uniform float contrast;

out vec4 FragColor;

float hash(vec2 p)
{
    p = fract(p * vec2(443.8975, 397.2973));
    p += dot(p, p + 19.19);
    return fract(p.x * p.y);
}

float grayAt(vec2 uv)
{
    vec3 color = texture(screenTexture, clamp(uv, 0.0, 1.0)).rgb;
    return dot(color, vec3(0.299, 0.587, 0.114));
}

vec2 lensUv(vec2 uv)
{
    vec2 dir = uv - blackHoleScreenPos;
    float dist = length(dir);
    float influence = 1.0 - smoothstep(0.05, 0.46, dist);
    float strength = 0.018 / (dist * dist + 0.035);
    vec2 safeDir = dir / max(dist, 0.0001);
    return uv - safeDir * strength * influence;
}

void main()
{
    vec2 uv = TexCoord;

    if (!enablePost) {
        float gray = grayAt(uv);
        FragColor = vec4(vec3(gray), 1.0);
        return;
    }

    vec2 warpedUv = lensUv(uv);
    float gray = grayAt(warpedUv);

    vec2 px = 1.0 / max(resolution, vec2(1.0));
    vec2 offsets[8] = vec2[](
        vec2( 1.5,  0.0),
        vec2(-1.5,  0.0),
        vec2( 0.0,  1.5),
        vec2( 0.0, -1.5),
        vec2( 2.2,  2.2),
        vec2(-2.2,  2.2),
        vec2( 2.2, -2.2),
        vec2(-2.2, -2.2)
    );

    float bloom = 0.0;
    for (int i = 0; i < 8; ++i) {
        float sampleGray = grayAt(warpedUv + offsets[i] * px);
        bloom += max(sampleGray - 0.55, 0.0);
    }
    bloom /= 8.0;
    gray += bloom * bloomStrength;

    gray = (gray - 0.5) * contrast + 0.5;

    float distToCenter = length(uv - vec2(0.5));
    float vignette = 1.0 - smoothstep(0.32, 0.85, distToCenter) * vignetteStrength;
    gray *= vignette;

    if (enableGrain) {
        float grain = (hash(gl_FragCoord.xy + time * 31.0) - 0.5) * grainStrength * 0.28;
        gray += grain;
    }

    gray = clamp(gray, 0.0, 1.0);
    FragColor = vec4(vec3(gray), 1.0);
}
