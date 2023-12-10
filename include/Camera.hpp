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

  Camera(vec3 position, vec3 rotation = vec3());
  ~Camera();

  mat4 getViewMatrix();
  mat4 getProjectionMatrix();
};

#endif

