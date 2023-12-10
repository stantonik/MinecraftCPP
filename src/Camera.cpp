#include "Camera.hpp"

Camera::Camera(vec3 position, vec3 rotation) : Object(position, rotation)
{
  //id = ++cameraCount;
}

Camera::~Camera()
{
  //cameraCount--;
}

mat4 Camera::getViewMatrix()
{
  return lookAt(position, position + forward(), sWorldUp);
}

mat4 Camera::getProjectionMatrix()
{
  return perspective(radians(fov), size.x / size.y, nearClipping, farClipping);
}

