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
    float x = -sin(radians(rotation.z));
    float y = cos(radians(rotation.x)) + cos(radians(rotation.z));
    float z = sin(radians(rotation.x));
    return glm::normalize(vec3(x, y, z));
  }

  vec3 right()
  {
    return glm::normalize(-cross(up(), forward()));
  }

  vec3 forward()
  {
    float x = sin(radians(rotation.y));
    float y = -sin(radians(rotation.x));
    float z = -cos(radians(rotation.y)) - cos(radians(rotation.x));
    return glm::normalize(vec3(x, y, z));
  }

private:
};

#endif

