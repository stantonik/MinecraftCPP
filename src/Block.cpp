#include "Block.hpp"

Block::Block() : Object()
{

}

Block::Block(int x, int y, int z, const char *name, unsigned int id, Direction orientation) : Object(glm::vec3(x, y, z))
{
  this->id = id;
  this->name = name;
  switch (orientation) {
    case Direction::FORWARD:
      rotation = glm::vec3(0, 0, 0);
      break;
    case Direction::BACKWARD:
      rotation = glm::vec3(0, 180, 0);
      break;
    case Direction::RIGTH:
      rotation = glm::vec3(0, -90, 0);
      break;
    case Direction::LEFT:
      rotation = glm::vec3(0, 90, 0);
      break;
    case Direction::UP:
      rotation = glm::vec3(-90, 0, 0);
      break;
    case Direction::DOWN:
      rotation = glm::vec3(90, 0, 0);
      break;
  }
}

Block::Block(const Block &block) : Object(block)
{
  textures = block.textures; 
  isTransparent = block.isTransparent;
}

void Block::getData(std::ifstream &file)
{
  // TODO: perfomence improvement
  json data;
  data = json::parse(file);

  std::string main_texture;
  std::map<std::string, std::string> alt_textures;
  data["main_texture"].get_to(main_texture);
  data["alt_textures"].get_to(alt_textures);

  textures.clear();

  textures.emplace_back(alt_textures["front_face"].size() > 0 ? alt_textures["front_face"] : main_texture);
  textures.emplace_back(alt_textures["back_face"].size() > 0 ? alt_textures["back_face"] : main_texture);
  textures.emplace_back(alt_textures["right_face"].size() > 0 ? alt_textures["right_face"] : main_texture);
  textures.emplace_back(alt_textures["left_face"].size() > 0 ? alt_textures["left_face"] : main_texture);
  textures.emplace_back(alt_textures["top_face"].size() > 0 ? alt_textures["top_face"] : main_texture);
  textures.emplace_back(alt_textures["bottom_face"].size() > 0 ? alt_textures["bottom_face"] : main_texture);
}

void Block::update()
{
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit); 
  try
  {
    std::string path = "res/blockdata/";
    path += std::string(name);
    path += ".json";
    file.open(path);
  }
  catch (std::ifstream::failure &e)
  {
    std::cerr << "Data for " << name << " block not loaded : " << e.what() << std::endl;
  }
  if (file)
  {
    getData(file);
    file.close();
  }
}


