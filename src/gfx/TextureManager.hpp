#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <iostream>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include "gfx/Texture.hpp"


class TextureManager
{
public:
  TextureManager (); 
  ~TextureManager ();

  int importTexture(const char *path);
  int importAll(const char *dirPath);
  int loadTextureCollage();
  Texture *getTexture(const char *name);

  const unsigned int &width, &height;
  const unsigned int &textureCount;

private:
  std::vector<Texture> mTextures;
  std::map<std::string, unsigned int> mTextureIds;
  unsigned char *mCollage;
  unsigned int mWidth, mHeight;
  unsigned int mTexCount = 0;

  void createCollage();

};

#endif

