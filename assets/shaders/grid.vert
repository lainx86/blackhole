#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

out float vFade;

void main()
{
    float r = length(aPos.xz);
    vFade = 1.0 - smoothstep(3.0, 10.5, r);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
