/*
 * File:   ShaderManager.h
 * Author: daddy
 *
 * Created on September 29, 2013, 12:40 PM
 */

#ifndef SHADERMANAGER_H
#define	SHADERMANAGER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <map>
#include <string>

struct ShaderInfo
{
  GLuint programID;
  std::string vertexName;
  std::string fragmentName;
};

class ShaderManager {
public:
  ShaderManager();
  ~ShaderManager();

  void Initialize();

  GLuint LoadProgramFromFile(std::string name, std::string fragmentShader, std::string vertexShader);
  GLuint LoadProgram(std::string name, std::string fragmentShader, std::string vertexShader,
                     std::string vertexShaderName="Vertex shader from string",
                     std::string fragmentShaderName="Fragment shader from string");

  void UseProgram(std::string name)
  {
    glUseProgram(programs[name].programID);
  }

private:
  std::map<std::string, ShaderInfo> programs;
};

#endif	/* SHADERMANAGER_H */

