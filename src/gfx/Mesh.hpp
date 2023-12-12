#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
};

class Mesh
{
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  Mesh ();
  ~Mesh ();

  void upload() const;
  void draw() const;
  void clear();

private:
  unsigned int VAO, VBO, EBO;
};

#endif

