/* 
 * File:   SceneManager.cpp
 * Author: daddy
 * 
 * Created on September 28, 2013, 12:43 PM
 */

#include "SceneManager.h"
#include "../Util/Log.h"

SceneManager::SceneManager()
{
  Title = "SDL GL Program";
  
  Width = 1024;
  Height = 600;
  
  RedBits = 8;
  GreenBits = 8;
  BlueBits = 8;
  AlphaBits = 8;

  DoubleBuffer = true;
  DepthBits = 8;
  StencilBits = 8;
  AccumRedBits = 8;
  AccumGreenBits = 8;
  AccumBlueBits = 8;
  AccumAlphaBits = 8;
  StereoBuffer = false;
  MultiSample = false;
  MultiSampleBits = 0;
  VSync = 0;
  FullScreen = false;
  MouseVisible = true;
  
  sdlInitialized = false;
  
  running = false;
  
  frames = 0;
  fps = 0;
  timer = 0;
  
  RootObject = nullptr;
}

SceneManager::~SceneManager()
{
}

bool SceneManager::InitWindow()
{
  if (SDL_Init(SDL_INIT_EVERYTHING ) < 0 )
  {
    Log(LogType::Error, "SDL Initialization failed\n");
    return false;    
  }
  else
  {
    sdlInitialized = true;
  }
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, RedBits);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, GreenBits);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, BlueBits);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, AlphaBits);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DoubleBuffer);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DepthBits);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, StencilBits);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, AccumRedBits);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, AccumGreenBits);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, AccumBlueBits);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, AccumAlphaBits);
  SDL_GL_SetAttribute(SDL_GL_STEREO, StereoBuffer);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, MultiSample);
  if (MultiSample)
  {
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, MultiSampleBits);
  }
  
  SDL_GL_SetSwapInterval(VSync);
  
  
  window = SDL_CreateWindow(
        Title.c_str(),                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        Width,                               // width, in pixels
        Height,                               // height, in pixels
        SDL_WINDOW_OPENGL     
    );
  
  if (window != nullptr)
  {
    glContext = SDL_GL_CreateContext(window);
  }
  
}

void SceneManager::CloseWindow()
{
  SDL_GL_DeleteContext(glContext);  
}
  
void SceneManager::MainLoop()
{
  SDL_Event event;
  timer = SDL_GetTicks();
  running = true;
  
  Initialize.Invoke(Width, Height);
  
  while( running ) {
    SDL_PollEvent( &event );
    switch( event.type ) 
    {
      case SDL_KEYDOWN: 
      {
        KeyDown.Invoke( event.key.keysym );
        break;
      }
      case SDL_KEYUP: 
      {
        KeyUp.Invoke( event.key.keysym );
        break;
      }      
      case SDL_QUIT: 
      {
        running = false;
        break;
      }
      case SDL_MOUSEWHEEL:
      {
        int scroll = ((event.wheel.y<0)?-1:((event.wheel.y>0)?1:0));
        MouseWheel.Invoke(scroll);
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        MouseButtonDown.Invoke(event.button.x, event.button.y, event.button.button);
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        MouseButtonUp.Invoke(event.button.x, event.button.y, event.button.button);
        break;
      }      
      case SDL_MOUSEMOTION:
      {
        MouseMove.Invoke(event.motion.x, event.motion.y);
        break;
      }
      case SDL_WINDOWEVENT_RESIZED:
      {
        Width = event.window.data1;
        Height = event.window.data2;
        Resize.Invoke(Width, Height);
        break;
      }
      default: 
      {
        render();
        break; 
      }
    }
  }  
}

void SceneManager::walkGLObjects(GLObject *object)
{
  if (object)
  {
    for (auto i : object->Children)
    {
      i->Render(Width, Height);
      walkGLObjects(i);
    }
  }
}

void SceneManager::render()
{
  Render.Invoke(Width, Height);
  walkGLObjects(RootObject);
  swapBuffers(); 
}
  
void SceneManager::Quit()
{
  running = false;
}

void SceneManager::swapBuffers()
{
  SDL_GL_SwapWindow( this->window );
	this->frames++;
	Uint32 now = SDL_GetTicks();
	if( now > (this->timer) ) {
		this->timer = now + 1000;
		this->fps = this->frames;
		this->frames = 0;
	}
}
