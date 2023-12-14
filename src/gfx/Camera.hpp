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

  //static Camera *main;
  //static unsigned int cameraCount;

  Camera(glm::vec3 position, glm::vec3 rotation = glm::vec3());
  ~Camera();

  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
};

#endif

