#include "Entity.hpp"
#include "World.hpp"

Entity::Entity() : Object()
{
  size = glm::vec3(0.8f, 1.8f, 0.5f);
}

Entity::Entity (glm::vec3 position, glm::vec3 rotation, World *world) : Object(position, rotation), world(world) 
{  
  size = glm::vec3(0.8f, 1.8f, 0.5f);
}

Entity::~Entity()
{
}

void Entity::attachCamera(Camera *camera)
{
  this->camera = camera;
  if (camera != nullptr)
  {
    // camera needs to be at eyes height
    float yoffset = (size.y - 0.5f);
    camera->position = this->position + glm::vec3(0, 1, 0) * yoffset;
  }
}

void Entity::move(glm::vec3 position)
{
  this->position += position;
  if (camera != nullptr)
  {
    camera->position += position; 
  }
}

void Entity::jump()
{
  if (grounded)
    velocity.y += sqrt(jumpHeight * 2 * g);
}

void Entity::checkIfGrounded()
{
  Block *block = world->getBlock(position - glm::vec3(0, 1, 0) * 0.5f);
  if (block != nullptr)
  {
    if (block->id != 0)
    {
      grounded = true;
      velocity.y = 0;
    }
    else grounded = false;
  }
  else
  {
    grounded = false;
  }
}

void Entity::kill()
{

}

void Entity::hit()
{

}

void Entity::gravity()
{
  if (!grounded && gravityAffected)
  {
    velocity.y += -g * world->deltaTime;
  }
}

void Entity::checkCollision()
{
  computeVectors();

  glm::vec3 checkPos = position;
  // check forward
  checkPos += glm::vec3(0, 0, size.z / 2.0f);
  Block *block = world->getBlock(checkPos);
  if (block != nullptr)
  {
    if (block->isSolid)
    {
      glm::vec3 normal(0, 0, -1);
    }
  }
}


