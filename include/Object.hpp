#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <string>
#include "Quaternion.hpp"

using namespace glm;


class Object
{
public:
  vec3 position;
  vec3 rotation;
  vec3 localPosition;
  vec3 localRotation;
  vec3 size;
  vec3 color;
  unsigned int id;
  std::string tag;
  std::string name;
  constexpr static vec3 sWorldUp = vec3(0.0f, 1.0f, 0.0f);

  Object() { Object(0, 0, 0); }
  Object(float x, float y, float z, float xrot = 0, float yrot = 0, float zrot = 0) { Object(vec3(x, y, z), vec3(xrot, yrot, zrot)); }    
  Object(vec3 position, vec3 rotation = vec3()) : position(position), rotation(rotation)
  {
    localPosition = position;
    localRotation = rotation;
    size = vec3();
    color = vec3();
    id = 0;
  }

  vec3 up()
  {
    computeVectors();
    return mUp;
  }

  vec3 right()
  {
    computeVectors();
    return mRigth;
  }

  vec3 forward()
  {
    computeVectors();
    return mForward;
  }

private:
  vec3 mForward = vec3(0, 0, -1);
  vec3 mRigth = vec3(1, 0, 0);
  vec3 mUp = vec3(0, 1, 0);

  const vec3 DEFAULT_FORWARD = vec3(0, 0, -1);
  const vec3 DEFAULT_RIGHT = vec3(1, 0, 0);
  const vec3 DEFAULT_UP = vec3(0, 1, 0);

  void computeVectors()
  {
    vec3 u = Quaternion::rotate(DEFAULT_FORWARD, -rotation.y, DEFAULT_UP);
    mRigth = Quaternion::rotate(DEFAULT_RIGHT, -rotation.y, DEFAULT_UP);
    
    mUp = Quaternion::rotate(DEFAULT_UP, -rotation.x, mRigth);
    mForward = Quaternion::rotate(u, -rotation.x, mRigth);
  }
};

#endif

