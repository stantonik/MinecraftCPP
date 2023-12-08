#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Shader.hpp"
#include "Camera.hpp"

GLFWwindow *window;
double dt = 0;

const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 600;
const char *TITLE = "Minecraft C++";

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

  if (glewInit() != GLEW_OK)
  {
    throw std::runtime_error("Could not initialize GLEW.");
  }

  // create a triangle
  Shader shader("res/shader/vertex.shader", "res/shader/fragment.shader");

  float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  double timer = 0;
  while(!glfwWindowShouldClose(window))
  {
    double previous_time = glfwGetTime();

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // render...
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // matrix transform
    mat4 projection(1.0f);
    mat4 view(1.0f);
    mat4 world(1.0f);

    world = rotate(world, (float)glfwGetTime() * radians(50.0f), vec3(1.0f, 0.0f, 1.0f));

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("world", world);
     

    glfwSwapBuffers(window);
    glfwPollEvents();

    double current_time = glfwGetTime();
    dt = current_time - previous_time;
    timer += dt;

    // display FPS in the title
    if (timer >= 0.2f)
    {
      std::string new_title = std::string(TITLE) + " : " + std::to_string(static_cast<int>(1.0f / dt)) + "FPS";
      glfwSetWindowTitle(window, new_title.c_str());
      timer = 0;
    } 
  }

  glfwTerminate();

  return 0;
}
