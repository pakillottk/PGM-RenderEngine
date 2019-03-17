#version 330 core
layout (location = 0) in vec3 vPos;
out vec4 color;

uniform float uniform1;
uniform int uniform2;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    color = vec4(uniform1, uniform1, uniform1, uniform2);

    // gl_Position = vec4(vPos, 1.0);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
}