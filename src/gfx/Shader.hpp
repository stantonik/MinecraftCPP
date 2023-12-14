#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Shader
{
public:
  Shader () {  }
  Shader (const char *pVertexShaderPath, const char *pFragmentShaderPath)
  {
    std::ifstream vertexShaderFile, fragmentShaderFile;
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
      vertexShaderFile.open(pVertexShaderPath);
      fragmentShaderFile.open(pFragmentShaderPath);
    } 
    catch (std::ifstream::failure &e) 
    {
      std::cerr << "Shader loading failed : " << e.what() << std::endl;
    }
    std::stringstream sstrVertexCode, sstrFragmentCode;
    sstrVertexCode << vertexShaderFile.rdbuf();
    sstrFragmentCode << fragmentShaderFile.rdbuf();
    vertexShaderFile.close();
    fragmentShaderFile.close();

    std::string strVertexCode = sstrVertexCode.str();
    std::string strFragmentCode = sstrFragmentCode.str();
    const char *vertexCode = strVertexCode.c_str();
    const char *fragmentCode = strFragmentCode.c_str();


    unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexCode, nullptr);
    glCompileShader(vertexID);
    checkError(vertexID, GL_COMPILE_STATUS);

    unsigned int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentID);
    checkError(fragmentID, GL_COMPILE_STATUS);

    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);
    checkError(programID, GL_LINK_STATUS);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
  }
  ~Shader ()
  {
    if (programID != 0)
      glDeleteProgram(programID);
  }

  void use() { glUseProgram(programID); }  

  void setVec3(const char *name, vec3 value)
  {
    GLint loc = glGetUniformLocation(programID, name);
    glUniform3fv(loc, 1, (float*)glm::value_ptr(value));
  }

  void setMat4(const char *name, mat4 value)
  {
    GLint loc = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float *)value_ptr(value));
  }

private:
  unsigned int programID = 0;

  void checkError(GLuint id, GLenum pname)
  {
    int success;
    char infoLog[512];

    if (pname == GL_COMPILE_STATUS)
    {
      glGetShaderiv(id, GL_COMPILE_STATUS, &success);
      if (!success)
      {
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "Shader compiling failed : " << infoLog << std::endl;
      }
    }
    else if (pname == GL_LINK_STATUS)
    {
      glGetProgramiv(programID, pname, &success);
      if (!success)
      {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "Program linking failed : " << infoLog << std::endl;
      }
    }
  }
};

#endif

