#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "Entity.hpp"
#include "World.hpp"
#include <GLFW/glfw3.h>
#include "utils/DDA.hpp"

struct Mouse
{
  bool firstMouse = true;
  double lastx;
  double lasty;
  double x;
  double y;
  double dx;
  double dy;
};

struct KeyBoard
{

};

class InputManager
{
public:
  float mouseSensivity = 50.0f;
  float deltaTime = 0;

  GLFWwindow *window;
  Entity *entity;
  Camera *camera;

  Mouse mouse;
  KeyBoard keyBoard;

  InputManager (GLFWwindow *window, Entity *entity);
  ~InputManager ();

  void update(float &deltaTime);

private:
  static void cursorCallback(GLFWwindow *window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  static bool intersectionCallback(World *world, glm::vec3 pos, glm::vec3 *intersectionHistory, unsigned int intersectionCount);
};

#endif

