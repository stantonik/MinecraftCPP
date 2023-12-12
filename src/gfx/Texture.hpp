#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>

struct Texture
{
  unsigned char *data;
  std::string name;
  glm::vec2 uvs[4] = { glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1) };
  int width, height, channelCount;
};

#endif

