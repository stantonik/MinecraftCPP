#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"


class Player : public Entity 
{
public:
  Player();
  Player(glm::vec3 position, glm::vec3 rotation, World *world); 
  ~Player ();

  void update() override;
};

#endif

