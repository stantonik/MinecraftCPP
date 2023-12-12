#include "Chunk.hpp"
#include "World.hpp"

Chunk::Chunk()
{
}

Chunk::Chunk(int x, int z, World *world) : Object()
{
  localPosition = glm::vec3(x, 0, z);
  position = localPosition * static_cast<float>(WIDTH_IN_BLOCK);
  grid = new Block*[WIDTH_IN_BLOCK * WIDTH_IN_BLOCK * HEIGTH_IN_BLOCK];
}

Chunk::~Chunk()
{
  if (grid) delete[] grid;
}

void Chunk::generate()
{
  populate();
  updateMesh();
}

void Chunk::populate()
{
  blocks.clear();
  // create the chunk
  for (int y = 0; y < HEIGTH_IN_BLOCK; y++)
    for (int x = 0; x < WIDTH_IN_BLOCK; x++)
      for (int z = 0; z < WIDTH_IN_BLOCK; z++)
      {
        glm::vec3 pos = glm::vec3(x, y, z) + this->position;
        Block *block = new Block(pos.x, pos.y, pos.z);
        block->localPosition = glm::vec3(x, y, z);
        if (y == 0) block->name = "oak_planks";
        else block->name = "dirt";
        block->id = 1;
        block->isTransparent = false;

        block->update();
        setBlock(block);
      }
}

void Chunk::setBlock(Block *block)
{
  int index = block->localPosition.x + (WIDTH_IN_BLOCK * block->localPosition.y) + (WIDTH_IN_BLOCK * HEIGTH_IN_BLOCK * block->localPosition.z);

  grid[index] = block;
  blocks.emplace_back(block);
}

Block *Chunk::getBlock(int x, int y, int z)
{
  if (x < 0 || x > WIDTH_IN_BLOCK - 1) return nullptr;
  if (y < 0 || y > HEIGTH_IN_BLOCK - 1) return nullptr;
  if (z < 0 || z > WIDTH_IN_BLOCK - 1) return nullptr;

  int index = x + (WIDTH_IN_BLOCK * y) + (WIDTH_IN_BLOCK * HEIGTH_IN_BLOCK * z);

  return grid[index];
}

void Chunk::updateMesh()
{
  if (texManager->textureCount <= 0) return;
  mesh.clear();

  unsigned int vertexCount = 0;

  for (Block *block : blocks)
  {
    if (block->id != 0)
    {
      for (int f = 0; f < 6; f++)
      {
        glm::vec3 neighborBlockPos = block->localPosition + Block::normals[f];
        Block *neighborBlock = getBlock(neighborBlockPos.x, neighborBlockPos.y, neighborBlockPos.z);
        bool display;
        if (neighborBlock == nullptr) display = true;
        else display = neighborBlock->isTransparent;
        if (display)
        {
          Texture *texture = nullptr;
          if (!block->textures.empty()) texture = texManager->getTexture(block->textures[f].c_str());

          for (int v = 0; v < 6; v++)
          {
            Vertex vertex = Block::vertices[Block::indices[v + f * 6]];
            vertex.position += block->position;
            if (texture) vertex.uv = texture->uvs[Block::uvIndices[v]];
            mesh.vertices.push_back(vertex);
            mesh.indices.push_back(vertexCount++);
          }
        }
      }
    }
  }

  mesh.upload();
}

glm::vec3 Chunk::localToGlobalPosition(glm::vec3 localPos)
{
  throw std::runtime_error("Not implemented yet."); 
}

glm::vec3 Chunk::globalToLocalPosition(glm::vec3 globalPos, glm::vec3 *chunkPos)
{
  glm::vec3 _chunkPos = glm::vec3();
  float whole, xfrac, zfrac;
  xfrac = std::modf(globalPos.x, &whole);
  int ix = static_cast<int>(whole) % WIDTH_IN_BLOCK;
  _chunkPos.x = whole / WIDTH_IN_BLOCK;
  zfrac = std::modf(globalPos.z, &whole);
  int iz = static_cast<int>(whole) % WIDTH_IN_BLOCK;
  _chunkPos.z = whole / WIDTH_IN_BLOCK;
  _chunkPos = floor(_chunkPos);
  if (chunkPos != nullptr) *chunkPos = _chunkPos;

  return glm::vec3(ix + xfrac, globalPos.y, iz + zfrac);
}


