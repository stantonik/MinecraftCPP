#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "Chunk.hpp"

class World
{
public:
  static const unsigned int SIZE_IN_CHUNK = 2;
  static const unsigned int SIZE_IN_BLOCK = SIZE_IN_CHUNK * Chunk::WIDTH_IN_BLOCK;

  World ();
  ~World ();

  void generate(TextureManager *texManager);
  
  Chunk *getChunk(glm::vec3 globalPos);
  Block *getBlock(glm::vec3 globalPos, Chunk **chunk = nullptr);
  void setBlock(Block block, Chunk **chunk = nullptr);

  Chunk *chunks[SIZE_IN_CHUNK][SIZE_IN_CHUNK];
};

#endif

