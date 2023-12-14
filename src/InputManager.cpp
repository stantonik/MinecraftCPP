#include "InputManager.hpp"

InputManager::InputManager(GLFWwindow *window, Entity *entity) : window(window), entity(entity)
{
  camera = entity->camera;
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, cursorCallback);  
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetKeyCallback(window, keyCallback);

  // hide and lock cursor in the middle
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

  glm::vec3 dpos = glm::vec3();

  float speed = entity->speed;
  if (glfwGetKey(window, GLFW_KEY_W))
    dpos = (float)deltaTime * forward * speed; 
  else if (glfwGetKey(window, GLFW_KEY_S))
    dpos = - (float)deltaTime * forward * speed; 
  if (glfwGetKey(window, GLFW_KEY_D))
    dpos = (float)deltaTime * camera->right() * speed; 
  else if (glfwGetKey(window, GLFW_KEY_A))
    dpos = - (float)deltaTime * camera->right() * speed; 
  /* if (glfwGetKey(window, GLFW_KEY_SPACE)) */
  /*   dpos = (float)deltaTime * camera->sWorldUp * speed; */ 
  /* else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) */
  /*   dpos = - (float)deltaTime * camera->sWorldUp * speed; */ 
  if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, true);

  entity->move(dpos);
  entity->move(entity->velocity * deltaTime);

  entity->checkIfGrounded();
  entity->gravity();
  if (glfwGetKey(window, GLFW_KEY_SPACE))
    entity->jump();
}

void InputManager::cursorCallback(GLFWwindow *window, double xpos, double ypos)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
  Mouse &mouse = inputManager->mouse;
  Camera *camera = inputManager->camera;

  if (mouse.firstMouse)
  {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    mouse.lastx = width / 2.0;
    mouse.lasty = height / 2.0;
    glfwSetCursorPos(window, mouse.lastx, mouse.lasty);
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
  camera->rotation.x += float(mouse.dy) * inputManager->mouseSensivity / 100.0f;
  camera->rotation.y += float(mouse.dx) * inputManager->mouseSensivity / 100.0f;
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
  Entity *entity = inputManager->entity;

  if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
  {
    Utils::DDA dda;
    dda.maxDistance = 6;
    dda.world = entity->world;
    dda.onCollisionCallback = InputManager::intersectionCallback; 
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
    {
      //clickable = false;
      dda.ray(entity->camera->position, entity->camera->forward());
    }
  } 
}

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  InputManager *inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
  Camera *camera = inputManager->camera;

}


bool InputManager::intersectionCallback(World *world, glm::vec3 pos, glm::vec3 *intersectionHistory, unsigned int intersectionCount)
{
  Chunk *actualChunk;
  // weird that we have to add 1 to the z component -> check DDA algo
  Block *block = world->getBlock(pos + glm::vec3(0, 0, 1), &actualChunk);
  if (block != nullptr)
  {
    if (block->id == 0) return true;

    block->id = 0;
    block->isTransparent = true;
    actualChunk->updateMesh();
    return false;

    /* Chunk *preBlockChunk; */
    /* glm::vec3 prePos = glm::vec3(); */
    /* if (intersectionCount >= 2) */
    /*   prePos = intersectionHistory[intersectionCount - 1 - 1]; */
    /* else return false; */ 
    /* Block *preBlock = world->getBlock(prePos, &preBlockChunk); */
    /* if (preBlock != nullptr) */
    /* { */
    /*   if (preBlockChunk == nullptr) return false; */
    /*   if (preBlock->id == 0) */
    /*   { */
    /*     preBlock->id = 3; */
    /*     preBlock->name = "cobblestone"; */
    /*     preBlock->update(); */
    /*     preBlockChunk->updateMesh(); */
    /*   } */
    /*   return false; */
    /* } */ 
    /* else return true; */

  }
  return true;
}

