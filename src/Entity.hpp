#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Object.hpp"
#include "gfx/Camera.hpp"

class World;

class Entity : public Object
{
public:
  
  float jumpHeight = 1.5f;
  float walkSpeed = 7.0f;
  float sprintSpeed = 13.0f;
  float speed = walkSpeed;
  bool grounded = false;
  float g = 15.0f;
  bool gravityAffected = true;
  float masse = 1;

  Camera *camera;
  World *world;
  bool isControlled = false;
  glm::vec3 velocity;

  Entity(); 
  Entity (glm::vec3 position, glm::vec3 rotation, World *world);
  ~Entity ();

  virtual void update() = 0; 

  void attachCamera(Camera *camera);
  void move(glm::vec3 position);
  void jump();
  virtual void kill();
  virtual void hit();

  void checkIfGrounded();
  void checkCollision();

  void gravity();
};

#endif

