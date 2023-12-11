#include "Chunk.hpp"

Chunk::Chunk()
{
}

Chunk::Chunk(int x, int z) : Object()
{
  localPosition = vec3(x, 0, z);
  position = localPosition * static_cast<float>(WIDTH_IN_BLOCK);
}

Chunk::~Chunk()
{
}

void Chunk::generate()
{
  populate();
  updateMesh();
}

void Chunk::populate()
{
  for (int y = 0; y < HEIGTH_IN_BLOCK; y++)
    for (int x = 0; x < WIDTH_IN_BLOCK; x++)
      for (int z = 0; z < WIDTH_IN_BLOCK; z++)
      {
        vec3 pos = vec3(x, y, z) + this->position;
        Block block(pos.x, pos.y, pos.z);
        if (y == 0) block.id = 0;
        else block.id = 1;
        setBlock(block);
      }
}

void Chunk::setBlock(Block &block)
{
  grid[(int)block.position.x][(int)block.position.y][(int)block.position.z] = &block;
  blocks.emplace_back(block);
}

Block Block::*getBlock(int x, int y, int z)
{
  return nullptr;
}

void Chunk::updateMesh()
{
  mesh.clear();

  unsigned int vertexCount = 0;

  for (Block &block : blocks)
  {
    for (int f = 0; f < 6; f++)
    {
      Texture &texture = texManager->mTextures[block.id];
      for (int v = 0; v < 6; v++)
      {
        Vertex vertex = Block::vertices[Block::indices[v + f * 6]];
        vertex.position += block.position;
        vertex.uv = texture.uvs[Block::uvIndices[v]];
        mesh.vertices.push_back(vertex);
        mesh.indices.push_back(vertexCount++);
      }
    }
  }

  mesh.upload();
}


