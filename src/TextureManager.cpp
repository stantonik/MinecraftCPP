#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace fs=std::filesystem;

TextureManager::TextureManager()
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
}

TextureManager::~TextureManager()
{
  for (Texture &texture : mTextures)
  {
    stbi_image_free(texture.data);
  }
}

int TextureManager::importTexture(const char *path)
{
  fs::path rPath = path;
  std::string filename = rPath.filename();

  Texture texture;
  texture.name = filename;
  texture.data = stbi_load(path, &texture.width, &texture.height, &texture.channelCount, 0);
  if(!texture.data)
  {
    std::cerr << "Failed to import texture at : " << path << std::endl;
    return -1;
  }

  mTextures.emplace_back(texture);
  return 0;
}

int TextureManager::loadTextures()
{
  Texture &texture = mTextures[0];
  mData = texture.data;
  if (mData)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cerr << "Failed to load texture on GPU." << std::endl;
    return -1;
  }
  return 0;
}

