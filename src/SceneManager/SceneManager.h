/* 
 * File:   SceneManager.h
 * Author: daddy
 *
 * Created on September 28, 2013, 12:43 PM
 */

#ifndef SCENEMANAGER_H
#define	SCENEMANAGER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include "../Util/Event.h"
#include "GLObject.h"

class SceneManager {
public:
  SceneManager();
  virtual ~SceneManager();
  
  bool InitWindow();
  void CloseWindow();
  
  void MainLoop();
  void Quit();
  
  Event<int, int> Initialize;
  Event<int, int> Render;
  Event<int, int> Resize;
  Event<SDL_Keysym> KeyDown;
  Event<SDL_Keysym> KeyUp;
  Event<int> MouseWheel;
  Event<int, int> MouseMove;
  Event<int, int, int> MouseButtonDown;
  Event<int, int, int> MouseButtonUp;
  
  GLObject *RootObject;
public:
  int RedBits;
  int GreenBits;
  int BlueBits;
  int AlphaBits;
  int Width;
  int Height;
  bool DoubleBuffer;
  int DepthBits;
  int StencilBits;
  int AccumRedBits;
  int AccumGreenBits;
  int AccumBlueBits;
  int AccumAlphaBits;
  bool StereoBuffer;
  bool MultiSample;
  int MultiSampleBits;
  int VSync;
  bool FullScreen;
  bool MouseVisible;
  
  std::string Title;
  
private:
  void swapBuffers();
  void render();
  void walkGLObjects(GLObject *object);
  
  SDL_Window *window; 
  SDL_GLContext glContext; 
    
  bool sdlInitialized;
  
  bool running;
  
  int frames;
  int fps;
  unsigned int timer;
  
};

#endif	/* SCENEMANAGER_H */

