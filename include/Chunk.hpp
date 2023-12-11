#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Object.hpp"
#include "Block.hpp"
#include "Mesh.hpp"
#include "TextureManager.hpp"
#include <vector>


class Chunk : public Object
{
public:
  static constexpr unsigned int WIDTH_IN_BLOCK = 5;
  static constexpr unsigned int HEIGTH_IN_BLOCK = 2;

  Mesh mesh;

  Chunk ();
  Chunk (int x, int z);
  ~Chunk ();

  void generate();
  void setBlock(Block &block);
  Block *getBlock(int x, int y, int z);
  TextureManager *texManager;

private:
  Block *grid[WIDTH_IN_BLOCK][WIDTH_IN_BLOCK][HEIGTH_IN_BLOCK];
  std::vector<Block> blocks;

  void populate();
  void updateMesh();
};

#endif

