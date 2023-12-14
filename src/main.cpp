#include <vector>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "gfx/TextureManager.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "utils/DDA.hpp"


GLFWwindow *window;
float dt = 0;

const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 600;
const char *TITLE = "Minecraft C++";
bool VSYNC = false;

void windowSizeCallback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

int main()
{
  /* -- GLFW INIT -- */
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);

  window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE, nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, windowSizeCallback);

  if (glewInit() != GLEW_OK) throw std::runtime_error("Could not initialize GLEW.");

  glEnable(GL_DEPTH_TEST);
  Shader shader("res/shader/vertex.shader", "res/shader/fragment.shader");

  // TEXTURES
  TextureManager texManager;
  texManager.importAll("res/texture");
  texManager.loadTextureCollage();

  // WORLD
  World world(dt);
  world.generate(&texManager);

  Camera camera(vec3(0, 0, 2));
  camera.size.x = DEFAULT_WIDTH;
  camera.size.y = DEFAULT_HEIGHT;

  // INPUT MANAGER
  world.players[0]->attachCamera(&camera);
  InputManager inputManager(window, world.players[0]);
  glfwSetWindowUserPointer(window, &inputManager);
  glfwSwapInterval(VSYNC);


  // matrix transform
  mat4 projection(1.0f);
  mat4 view(1.0f);
  mat4 model(1.0f);

  /* GAME LOOP */
  double timer = 0;
  double previous_time = glfwGetTime();
  unsigned int frameCount = 0;
  while(!glfwWindowShouldClose(window))
  {
    double current_time = glfwGetTime();
    dt = current_time - previous_time;
    previous_time = current_time;
    timer += dt;
    frameCount++;
    // display FPS in the title
    if (timer >= 0.5f)
    {
      unsigned int fps = frameCount / 0.5f;
      std::string new_title = std::string(TITLE) + " : " + std::to_string(static_cast<int>(fps)) + "FPS";
      glfwSetWindowTitle(window, new_title.c_str());
      timer = 0;
      frameCount = 0;
    } 

    glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwPollEvents();

    // render...
    shader.use();
    for (int x = 0; x < World::SIZE_IN_CHUNK; ++x)
      for (int z = 0; z < World::SIZE_IN_CHUNK; ++z)
      {
        Chunk *chunk = world.chunks[x][z];
        chunk->mesh.draw();
      }

    //get key input
    inputManager.update(dt);

    projection = camera.getProjectionMatrix(); 
    view = camera.getViewMatrix();

    // send uniform to shaders
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("world", model);
    shader.setVec3("sunPos", world.lightPos);

    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}
