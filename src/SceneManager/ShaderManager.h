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

class ShaderManager {
public:
  ShaderManager();
  ~ShaderManager();
  
  void LoadProgramFromFile(std::string name, std::string fragmentShader, std::string vertexShader);
  void LoadProgram(std::string name, std::string fragmentShader, std::string vertexShader);
  
  void UseProgram(std::string name)
  {
    glUseProgram(programs[name]);
  }
  
private:
  std::map<std::string, GLuint> programs;
};

#endif	/* SHADERMANAGER_H */

