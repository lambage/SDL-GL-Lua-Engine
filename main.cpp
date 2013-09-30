#include "Util/Log.h"
#include "SceneManager/SceneManager.h"
#include <stdio.h>


void Initialize(int w, int h)
{
  glClearColor(0.2f, 0.4f, 0.2f, 0.0f);
}

void Render(int w, int h)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char *argv[])
{
  SceneManager sceneManager;
  
  sceneManager.InitWindow();
  
  sceneManager.Initialize += Initialize;
  sceneManager.Render += Render;
  
  sceneManager.MainLoop();
  sceneManager.CloseWindow();    
    
  return 0;
}

