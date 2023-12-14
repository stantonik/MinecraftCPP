#version 330 core

in vec3 oPos;
in vec2 oUv;
in vec3 oNormal;

out vec4 color;

uniform sampler2D tex;
uniform vec3 sunPos;

void main()
{
  vec3 normal = normalize(oNormal);
  vec3 sunLightDir = normalize(sunPos - oPos);
  float kDiffuse = max(dot(normal, sunLightDir), 0.0);

  vec3 ambient = vec3(1, 1, 1) * 0.5;
  vec3 diffuse = vec3(1, 1, 1) * kDiffuse * 0.8;
  color = vec4((ambient + diffuse), 1.0) * texture(tex, oUv);
} 
