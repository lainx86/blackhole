#version 330 core

in float vFade;

out vec4 FragColor;

void main()
{
    float gray = 0.18 * vFade;
    float alpha = 0.24 * vFade;
    FragColor = vec4(vec3(gray), alpha);
}
