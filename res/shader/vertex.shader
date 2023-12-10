#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 oUv;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 world;

void main()
{
    gl_Position = projection * view * world * vec4(pos, 1.0f);
    oUv = uv;
}
