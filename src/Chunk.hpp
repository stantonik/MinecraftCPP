#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Object.hpp"
#include "Block.hpp"
#include "gfx/Mesh.hpp"
#include "gfx/TextureManager.hpp"
#include <vector>

// forward declaration to avoid circular dependency
class World;

class Chunk : public Object
{
public:
  static constexpr unsigned int WIDTH_IN_BLOCK = 16;
  static constexpr unsigned int HEIGTH_IN_BLOCK = 4;

  Mesh mesh;
  World *world;

  Chunk ();
  Chunk (int x, int z, World *world);
  ~Chunk ();

  void generate();
  void updateMesh();
  void setBlock(Block *block);
  Block *getBlock(int x, int y, int z);
  TextureManager *texManager;
  static glm::vec3 localToGlobalPosition(glm::vec3 localPos);
  static glm::vec3 globalToLocalPosition(glm::vec3 globalPos, glm::vec3 *chunkPos = nullptr);

private:
  Block **grid;
  std::vector<Block*> blocks;

  void populate();
};

#endif

