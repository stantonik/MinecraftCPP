#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 rotation) : Object(position, rotation)
{
  //id = ++cameraCount;
}

Camera::~Camera()
{
  //cameraCount--;
}

glm::mat4 Camera::getViewMatrix()
{
  return lookAt(position, position + forward(), sWorldUp);
}

glm::mat4 Camera::getProjectionMatrix()
{
  return glm::perspective(glm::radians(fov), size.x / size.y, nearClipping, farClipping);
}

