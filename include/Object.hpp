#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <string>

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

  Object(float x = 0, float y = 0, float z = 0, float xrot = 0, float yrot = 0, float zrot = 0) { Object(vec3(x, y, z), vec3(xrot, yrot, zrot)); }    
  Object(vec3 position = vec3(), vec3 rotation = vec3()) : position(position), rotation(rotation)
  {
    localPosition = position;
    localRotation = rotation;
    size = vec3();
    color = vec3();
    id = 0;
  }

  vec3 up()
  {
    float x = cos(rotation.y) - sin(rotation.z);
    float y = cos(rotation.x) + cos(rotation.z);
    float z = sin(rotation.x) - sin(rotation.y);
    return glm::normalize(vec3(x, y, z));
  }

  vec3 right()
  {
    return glm::normalize(vec3());
  }

  vec3 forward()
  {
    return glm::normalize(vec3());
  }

private:
};

#endif

