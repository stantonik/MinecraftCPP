#include <vector>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (glewInit() != GLEW_OK)
  {
    throw std::runtime_error("Could not initialize GLEW.");
  }

  // create a triangle
  glEnable(GL_DEPTH_TEST);
  Shader shader("res/shader/vertex.shader", "res/shader/fragment.shader");

  Vertex a = { vec3(0.5f, -0.5f, 0), vec3(0), vec2(0) };
  Vertex b = { vec3(-0.5f, -0.5f, 0), vec3(0), vec2(0) };
  Vertex c = { vec3(0, 0.5f, 0), vec3(0), vec2(0) };

  std::vector<Vertex> vertices { a, b, c };
  std::vector<unsigned int> indices { 0, 1, 2 };

  Mesh triangle;
  triangle.vertices = vertices;
  triangle.indices = indices;
  triangle.upload();

  Camera camera(vec3(0, 0, 2));
  camera.size.x = DEFAULT_WIDTH;
  camera.size.y = DEFAULT_HEIGHT;
  bool firstMouse = true;
  double xLastMouse, yLastMouse;
  // matrix transform
  mat4 projection(1.0f);
  mat4 view(1.0f);
  mat4 world(1.0f);


  double timer = 0;
  while(!glfwWindowShouldClose(window))
  {
    double previous_time = glfwGetTime();

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render...
    shader.use();
    triangle.draw();

    //get key input
    // project forward vector into (0, x, z) plan
    vec3 forward = camera.forward();
    forward.y = 0;
    forward = normalize(forward);

    float speed = 5;
    if (glfwGetKey(window, GLFW_KEY_W))
      camera.position += (float)dt * forward * speed; 
    else if (glfwGetKey(window, GLFW_KEY_S))
      camera.position -= (float)dt * forward * speed; 
    if (glfwGetKey(window, GLFW_KEY_D))
      camera.position += (float)dt * camera.right() * speed; 
    else if (glfwGetKey(window, GLFW_KEY_A))
      camera.position -= (float)dt * camera.right() * speed; 
    if (glfwGetKey(window, GLFW_KEY_SPACE))
      camera.position += (float)dt * camera.sWorldUp * speed; 
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
      camera.position -= (float)dt * camera.sWorldUp * speed; 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(window, true);
    
    //get mouse input
    double xmouse, ymouse;
    double dx = 0, dy = 0;
    glfwGetCursorPos(window, &xmouse, &ymouse);
    if (firstMouse)
    {
      xLastMouse = xmouse;
      yLastMouse = ymouse;
      firstMouse = false;
    }
    else 
    {
      dx = xmouse - xLastMouse;
      dy = ymouse - yLastMouse;
      xLastMouse = xmouse;
      yLastMouse = ymouse;
    }
    float mouseSensivity = 0.6f;
    camera.rotation.x += dy * mouseSensivity;
    camera.rotation.y += dx * mouseSensivity;
    if (camera.rotation.x > 89.0f) camera.rotation.x = 89.0f;
    if (camera.rotation.x < -89.0f) camera.rotation.x = -89.0f;

    projection = camera.getProjectionMatrix(); 

    view = camera.getViewMatrix();

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
