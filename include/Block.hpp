#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Mesh.hpp"
#include "Object.hpp"

enum class Direction
{
  FORWARD, BACKWARD, RIGTH, LEFT, UP, DOWN
};

class Block : public Object
{
public:
  static constexpr Vertex vertices[8]
  {
    Vertex { vec3(0, 0, -1), vec3(), vec2() },
    Vertex { vec3(1, 0, -1), vec3(), vec2() },
    Vertex { vec3(1, 1, -1), vec3(), vec2() },
    Vertex { vec3(0, 1, -1), vec3(), vec2() },
    Vertex { vec3(0, 0, 0),  vec3(), vec2() },
    Vertex { vec3(1, 0, 0),  vec3(), vec2() },
    Vertex { vec3(1, 1, 0),  vec3(), vec2() },
    Vertex { vec3(0, 1, 0),  vec3(), vec2() },
  };
  static constexpr unsigned int indices[6 * 6] 
  { 
    4, 5, 7, 7, 5, 6, // front
    1, 0, 2, 2, 0, 3, // back
    5, 1, 6, 6, 1, 2, // right
    0, 4, 3, 3, 4, 7, // left
    7, 6, 3, 3, 6, 2, // top
    0, 1, 4, 4, 1, 5, // bottom
  };
  static constexpr vec3 normals[6]
  {
    vec3(0, 0, 1), // front 
    vec3(0, 0, -1), // back
    vec3(1, 0, 0), // right
    vec3(-1, 0, 0), // left
    vec3(0, 1, 0), // top
    vec3(0, -1, 0), // bottom
  };
  static constexpr vec2 uvs[6]
  {
    vec2(0, 0), vec2(1, 0), vec2(0, 1), vec2(0, 1), vec2(1, 0), vec2(1, 1)
  };

  Block();
  Block(int x, int y, int z, unsigned int id = 0, Direction orientation = Direction::FORWARD);
};

#endif

