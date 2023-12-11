#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace fs=std::filesystem;

TextureManager::TextureManager() : width(mWidth), height(mHeight)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
}

TextureManager::~TextureManager()
{
  stbi_image_free(mCollage);
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

int TextureManager::loadTextureCollage()
{
  createCollage();
  if (mCollage)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mCollage);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cerr << "Failed to load texture on GPU." << std::endl;
    return -1;
  }
  return 0;
}

void TextureManager::createCollage()
{
  mHeight = mTextures[0].height;
  mWidth = 0;
  for (Texture &texture : mTextures) mWidth += texture.width;

  mCollage = new unsigned char[mHeight * mWidth * 4];
  for (int i = 0; i < mTextures.size(); ++i)
  {
    Texture &texture = mTextures[i];

    for (int j = 0; j < 4; ++j)
    {
      float step = 1.0f / static_cast<float>(mTextures.size());
      texture.uvs[j].x *= step; 
      texture.uvs[j].x += step * i;
    }

    for (int j = 0; j < mHeight; ++j)
    {
      int destOffset = mTextures.size() * texture.width * 4 * j + (i * texture.width * 4);
      int srcOffset = texture.width * j * 4;
      memcpy(mCollage + destOffset, texture.data + srcOffset, texture.width * 4);
    }
  }
}
