#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <GL/glew.h>

struct Texture
{
  unsigned char *data;
  std::string name;
  float u, v;
  int width, height, channelCount;
};

class TextureManager
{
public:
  TextureManager ();
  ~TextureManager ();

  int importTexture(const char *path);
  int loadTextures();

private:
  std::vector<Texture> mTextures;
  unsigned char *mData;

};

#endif

