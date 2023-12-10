#include "Block.hpp"

Block::Block() : Object()
{

}

Block::Block(int x, int y, int z, unsigned int id, Direction orientation) : Object(vec3(x, y, z))
{
  this->id = id;
  switch (orientation) {
    case Direction::FORWARD:
      rotation = vec3(0, 0, 0);
      break;
    case Direction::BACKWARD:
      rotation = vec3(0, 180, 0);
      break;
    case Direction::RIGTH:
      rotation = vec3(0, -90, 0);
      break;
    case Direction::LEFT:
      rotation = vec3(0, 90, 0);
      break;
    case Direction::UP:
      rotation = vec3(-90, 0, 0);
      break;
    case Direction::DOWN:
      rotation = vec3(90, 0, 0);
      break;
  }
}
