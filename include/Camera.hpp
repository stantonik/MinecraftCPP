#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Object.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Object
{
public:
  float fov = 45.0;
  float nearClipping = 0.1f;
  float farClipping = 100.0f;

  Camera(vec3 position, vec3 rotation = vec3()) : Object(position, rotation)
  {

  }

  mat4 getViewMatrix()
  {
    return lookAt(position, position + forward(), sWorldUp);
  }

  mat4 getProjectionMatrix()
  {
    return perspective(radians(fov), size.x / size.y, nearClipping, farClipping);
  }
};

#endif

