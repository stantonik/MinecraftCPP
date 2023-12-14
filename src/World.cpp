#include "World.hpp"

World::World(float &deltaTime) : deltaTime(deltaTime)
{
  
}

World::~World()
{
}

void World::generate(TextureManager *texManager)
{
  // generate chunks
  for (int x = 0; x < SIZE_IN_CHUNK; ++x)
    for (int z = 0; z < SIZE_IN_CHUNK; ++z)
    {
      Chunk *chunk = new Chunk(x, z, this);
      chunk->texManager = texManager;
      chunk->ySurface = 4;
      chunk->generate();
      chunks[x][z] = chunk;
    }

  // spawn entities

  Player *player = new Player(glm::vec3(5, 10, 5), glm::vec3(0), this);
  players.emplace_back(player);
  entities.emplace_back(player);
}

Chunk *World::getChunk(glm::vec3 globalPos)
{
  throw std::runtime_error("Not implemented yet");
}

Block *World::getBlock(glm::vec3 globalPos, Chunk **chunk)
{
  Chunk *_chunk;
  glm::vec3 chunkPos = glm::vec3();
  glm::vec3 localPos = floor(Chunk::globalToLocalPosition(globalPos, &chunkPos));
  if (chunkPos.x < 0 || chunkPos.x > SIZE_IN_CHUNK - 1) return nullptr;
  if (chunkPos.z < 0 || chunkPos.z > SIZE_IN_CHUNK - 1) return nullptr;

  _chunk = chunks[(int)chunkPos.x][(int)chunkPos.z];
  if (chunk != nullptr)
    *chunk = _chunk;

  return _chunk->getBlock(localPos.x, localPos.y, localPos.z);
}

void World::setBlock(Block block, Chunk **chunk)
{
  glm::vec3 chunkPos = glm::vec3();
  glm::vec3 localPos = floor(Chunk::globalToLocalPosition(block.position, &chunkPos));
  if (chunkPos.x < 0 || chunkPos.x > SIZE_IN_CHUNK - 1) return;
  if (chunkPos.z < 0 || chunkPos.z > SIZE_IN_CHUNK - 1) return;

  *chunk = chunks[(int)chunkPos.x][(int)chunkPos.z];

  Block *_block = (*chunk)->getBlock(localPos.x, localPos.y, localPos.z);
  *_block = block;
}
