#version 330 core

in vec2 oUv;

out vec4 color;

uniform sampler2D tex;

void main()
{
    //color = vec4(0.1f, 0.5f, 0.1f, 1.0f);
    color = texture(tex, oUv);
} 
