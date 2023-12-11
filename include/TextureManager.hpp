#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <GL/glew.h>
#include <glm/vec2.hpp>

struct Texture
{
  unsigned char *data;
  std::string name;
  glm::vec2 uvs[4] = { glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1) };
  int width, height, channelCount;
};

class TextureManager
{
public:
  TextureManager (); 
  ~TextureManager ();

  int importTexture(const char *path);
  int loadTextureCollage();

  const unsigned int &width, &height;
  std::vector<Texture> mTextures;

private:
  unsigned char *mCollage;
  unsigned int mWidth, mHeight;

  void createCollage();

};

#endif

