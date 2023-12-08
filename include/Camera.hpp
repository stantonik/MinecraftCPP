#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Object.hpp"

class Camera : public Object
{
public:
  float fov;

  mat4 getViewMatrix()
  {
    return mat4();
  }
};

#endif

