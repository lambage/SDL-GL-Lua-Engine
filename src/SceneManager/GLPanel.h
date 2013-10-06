/* 
 * File:   GLPanel.h
 * Author: daddy
 *
 * Created on September 29, 2013, 12:13 PM
 */

#ifndef GLPANEL_H
#define	GLPANEL_H

#include "GLObject.h"

class GLPanel : GLObject
{
public:
  GLPanel(SceneManager * sceneManager);
  virtual ~GLPanel();
  
  virtual void Render(int w, int h);
private:

};

#endif	/* GLPANEL_H */

