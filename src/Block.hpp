#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "gfx/Mesh.hpp"
#include "Object.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <map>

using json = nlohmann::json;

enum class Direction
{
  FORWARD, BACKWARD, RIGTH, LEFT, UP, DOWN
};

class Block : public Object
{
public:
  static constexpr Vertex vertices[8]
  {
    Vertex { glm::vec3(0, 0, -1), glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(1, 0, -1), glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(1, 1, -1), glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(0, 1, -1), glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(0, 0, 0),  glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(1, 0, 0),  glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(1, 1, 0),  glm::vec3(), glm::vec2() },
    Vertex { glm::vec3(0, 1, 0),  glm::vec3(), glm::vec2() },
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
  static constexpr glm::vec3 normals[6]
  {
    glm::vec3(0, 0, 1), // front 
    glm::vec3(0, 0, -1), // back
    glm::vec3(1, 0, 0), // right
    glm::vec3(-1, 0, 0), // left
    glm::vec3(0, 1, 0), // top
    glm::vec3(0, -1, 0), // bottom
  };
  static constexpr unsigned int uvIndices[6] { 0, 1, 3, 3, 1, 2 };

  std::vector<std::string> textures;
  bool isTransparent = true;
  bool isSolid = true;

  Block();
  Block(const Block &block);
  Block(int x, int y, int z, const char *name = "air", unsigned int id = 0, Direction orientation = Direction::FORWARD);
  void update();

private:
  void getData(std::ifstream &file);
};

#endif

