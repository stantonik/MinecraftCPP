#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "utils/Quaternion.hpp"

using namespace Utils;


class Object
{
public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 localPosition;
  glm::vec3 localRotation;
  glm::vec3 size;
  glm::vec3 color;
  unsigned int id;
  std::string tag;
  std::string name;
  constexpr static glm::vec3 sWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

  Object();
  Object(float x, float y, float z, float xrot = 0, float yrot = 0, float zrot = 0);
  Object(glm::vec3 position, glm::vec3 rotation = glm::vec3());
  Object(const Object &obj);

  Object &operator=(const Object &obj);

  glm::vec3 up();
  glm::vec3 right();
  glm::vec3 forward();

protected:
  glm::vec3 mForward = glm::vec3(0, 0, -1);
  glm::vec3 mRigth = glm::vec3(1, 0, 0);
  glm::vec3 mUp = glm::vec3(0, 1, 0);

  const glm::vec3 DEFAULT_FORWARD = glm::vec3(0, 0, -1);
  const glm::vec3 DEFAULT_RIGHT = glm::vec3(1, 0, 0);
  const glm::vec3 DEFAULT_UP = glm::vec3(0, 1, 0);

  void computeVectors();
};

#endif

