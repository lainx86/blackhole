#version 330 core

in float vBrightness;

uniform float grainStrength;
uniform float time;

out vec4 FragColor;

float hash(vec2 p)
{
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

void main()
{
    vec2 uv = gl_PointCoord * 2.0 - 1.0;
    float r = dot(uv, uv);
    if (r > 1.0) {
        discard;
    }

    float core = exp(-r * 2.6);
    float edge = 1.0 - smoothstep(0.58, 1.0, r);
    float shape = core * edge;
    float grain = (hash(gl_FragCoord.xy + time * 13.0) - 0.5) * grainStrength * 0.18;
    float b = clamp(vBrightness * (1.0 + grain), 0.0, 0.92);
    float alpha = shape * b * 0.82;

    FragColor = vec4(vec3(b), alpha);
}
