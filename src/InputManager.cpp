#include "InputManager.hpp"

InputManager::InputManager(GLFWwindow *window, Entity *entity, Camera *camera) : window(window), entity(entity), camera(camera)
{
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, cursorCallback);  
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetKeyCallback(window, keyCallback);

  // better control of the camera
  if (glfwRawMouseMotionSupported())
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

InputManager::~InputManager()
{
}

void InputManager::update(float &deltaTime)
{
  this->deltaTime = deltaTime;

  // project forward vector into (0, x, z) plan
  glm::vec3 forward = camera->forward();
  forward.y = 0;
  forward = normalize(forward);

  float speed = 5;
  if (glfwGetKey(window, GLFW_KEY_W))
    camera->position += (float)deltaTime * forward * speed; 
  else if (glfwGetKey(window, GLFW_KEY_S))
    camera->position -= (float)deltaTime * forward * speed; 
  if (glfwGetKey(window, GLFW_KEY_D))
    camera->position += (float)deltaTime * camera->right() * speed; 
  else if (glfwGetKey(window, GLFW_KEY_A))
    camera->position -= (float)deltaTime * camera->right() * speed; 
  if (glfwGetKey(window, GLFW_KEY_SPACE))
    camera->position += (float)deltaTime * camera->sWorldUp * speed; 
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
    camera->position -= (float)deltaTime * camera->sWorldUp * speed; 
  if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, true);

}

void InputManager::cursorCallback(GLFWwindow *window, double xpos, double ypos)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
  Mouse &mouse = inputManager->mouse;
  Camera *camera = inputManager->camera;

  if (mouse.firstMouse)
  {
    mouse.lastx = xpos;
    mouse.lasty = ypos;
    mouse.dx = 0;
    mouse.dy = 0;
    mouse.firstMouse = false;
  }
  else 
  {
    mouse.dx = xpos - mouse.lastx;
    mouse.dy = ypos - mouse.lasty;
    mouse.lastx = xpos;
    mouse.lasty = ypos;
  }
  camera->rotation.x += mouse.dy * inputManager->mouseSensivity / 100.0f;
  camera->rotation.y += mouse.dx * inputManager->mouseSensivity / 100.0f;
  if (camera->rotation.x > 89.0f) camera->rotation.x = 89.0f;
  if (camera->rotation.x < -89.0f) camera->rotation.x = -89.0f;
}

void InputManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

}

void InputManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

}

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
  Camera *camera = inputManager->camera;

}

