/* 
 * File:   GLObject.h
 * Author: daddy
 *
 * Created on September 29, 2013, 11:26 AM
 */

#ifndef GLOBJECT_H
#define	GLOBJECT_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../Util/Event.h"
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum class GLBorderStyle
{
  NoBorder,
  ThinBorder,
  ThickBorder
};

class SceneManager;

class GLObject {
public:
  GLObject(SceneManager * sceneManager);
  virtual ~GLObject();
  
  int X;
  int Y;
  int Width;
  int Height;
  std::string Text;
  
  glm::vec4 ForeColor;
  glm::vec4 BackColor;
  SDL_Texture *Image;
  
  GLBorderStyle BorderStyle;
  
  Event<SDL_Keysym> KeyDown;
  Event<SDL_Keysym> KeyUp;
  Event<int> MouseWheel;
  Event<int, int> MouseMove;
  Event<int, int, int> MouseButtonDown;
  Event<int, int, int> MouseButtonUp;
  
  virtual void Render(int w, int h) = 0;
  
  
  std::vector<GLObject *> Children;
  
private:

  SceneManager * sceneManager;
  GLuint vertexBuffer;
  GLuint uvBuffer;
  
};

#endif	/* GLOBJECT_H */

