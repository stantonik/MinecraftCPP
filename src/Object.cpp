#include "Object.hpp"

Object::Object() 
{ 
  Object(0, 0, 0); 
}

Object::Object(float x, float y, float z, float xrot, float yrot, float zrot) 
{
  Object(glm::vec3(x, y, z), glm::vec3(xrot, yrot, zrot)); 
}

Object::Object(glm::vec3 position, glm::vec3 rotation) : position(position), rotation(rotation)
{
  localPosition = position;
  localRotation = rotation;
  size = glm::vec3();
  color = glm::vec3();
  id = 0;
}

Object::Object(const Object &obj)
{
  position = obj.position;
  rotation = obj.rotation;
  localPosition = obj.localPosition;
  localRotation = obj.localRotation;
  size = obj.size;
  color = obj.color;
  id = obj.id;
  tag = obj.tag;
  name = obj.name;
}

Object &Object::operator=(const Object &obj) 
{ 
  position = obj.position;
  rotation = obj.rotation;
  localPosition = obj.localPosition;
  localRotation = obj.localRotation;
  size = obj.size;
  color = obj.color;
  id = obj.id;
  tag = obj.tag;
  name = obj.name;
  return *this; 
}

glm::vec3 Object::up()
{
  computeVectors();
  return mUp;
}

glm::vec3 Object::right()
{
  computeVectors();
  return mRigth;
}

glm::vec3 Object::forward()
{
  computeVectors();
  return mForward;
}

void Object::computeVectors()
{
  glm::vec3 u = Quaternion::rotateVector(DEFAULT_FORWARD, -rotation.y, DEFAULT_UP);
  mRigth = Quaternion::rotateVector(DEFAULT_RIGHT, -rotation.y, DEFAULT_UP);

  mUp = Quaternion::rotateVector(DEFAULT_UP, -rotation.x, mRigth);
  mForward = Quaternion::rotateVector(u, -rotation.x, mRigth);
}

