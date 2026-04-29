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
uniform float eventHorizonRadius;
uniform float shadowRadius;
uniform float photonRingRadius;
uniform float photonRingWidth;
uniform float photonRingIntensity;
uniform float lensStrength;
uniform float screenAspect;

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

vec2 blackHoleVector(vec2 uv)
{
    return vec2((uv.x - blackHoleScreenPos.x) * max(screenAspect, 0.0001), uv.y - blackHoleScreenPos.y);
}

float blackHoleDistance(vec2 uv)
{
    return length(blackHoleVector(uv));
}

vec2 lensUv(vec2 uv)
{
    float visualShadowRadius = max(shadowRadius, 0.001);
    float ringRadius = max(photonRingRadius, visualShadowRadius);
    vec2 dir = blackHoleVector(uv);
    float dist = length(dir);
    vec2 safeDir = dir / max(dist, 0.0001);

    float ringFalloff = 1.0 - smoothstep(
        max(photonRingWidth, 0.0008) * 0.5,
        max(photonRingWidth, 0.0008) * 5.5,
        abs(dist - ringRadius)
    );
    float influence = 1.0 - smoothstep(visualShadowRadius * 1.05, visualShadowRadius * 5.2, dist);
    float deflection = lensStrength * visualShadowRadius * visualShadowRadius /
        max(dist, visualShadowRadius * 0.72);
    deflection *= influence * (0.34 + 0.50 * ringFalloff);

    vec2 uvDir = vec2(safeDir.x / max(screenAspect, 0.0001), safeDir.y);
    return uv - uvDir * deflection;
}

float photonRingMask(float dist)
{
    float width = max(photonRingWidth, 0.0008);
    float ringRadius = max(photonRingRadius, max(shadowRadius, 0.001));
    float core = 1.0 - smoothstep(width * 0.35, width * 1.35, abs(dist - ringRadius));
    float halo = 1.0 - smoothstep(width * 1.4, width * 4.5, abs(dist - ringRadius));
    return clamp(core + halo * 0.18, 0.0, 1.0);
}

float applyBlackHoleOptics(float gray, vec2 uv)
{
    float eventRadius = max(eventHorizonRadius, 0.0008);
    float visualShadowRadius = max(shadowRadius, eventRadius * 1.6);
    float dist = blackHoleDistance(uv);
    float horizonCore = 1.0 - smoothstep(eventRadius * 0.60, eventRadius * 1.25, dist);
    float shadow = 1.0 - smoothstep(visualShadowRadius * 0.94, visualShadowRadius * 1.045, dist);
    float penumbra = 1.0 - smoothstep(visualShadowRadius * 1.02, visualShadowRadius * 1.22, dist);

    gray *= 1.0 - shadow * 0.985;
    gray *= 1.0 - horizonCore * 0.35;
    gray *= 1.0 - penumbra * 0.22;

    float outsideShadow = smoothstep(visualShadowRadius * 0.96, visualShadowRadius * 1.02, dist);
    float ring = photonRingMask(dist);
    float direction = blackHoleVector(uv).x / max(dist, 0.0001);
    float ringAsymmetry = 0.90 + 0.10 * direction;
    float innerGlow = exp(-pow(
        (dist - visualShadowRadius * 1.22) / max(visualShadowRadius * 0.42, 0.0008),
        2.0
    ));

    gray += outsideShadow * ring * photonRingIntensity * ringAsymmetry;
    gray += outsideShadow * innerGlow * 0.055;

    return gray;
}

void main()
{
    vec2 uv = TexCoord;
    vec2 warpedUv = enablePost ? lensUv(uv) : uv;
    float gray = grayAt(warpedUv);

    if (enablePost) {
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
    }

    if (enableGrain) {
        float grain = (hash(gl_FragCoord.xy + time * 31.0) - 0.5) * grainStrength * 0.28;
        gray += grain;
    }

    gray = applyBlackHoleOptics(gray, uv);
    gray = clamp(gray, 0.0, 1.0);
    FragColor = vec4(vec3(gray), 1.0);
}
