#include "framework/OpenGLHeaders.h"
#ifndef OPENGLUTILS_H_
#define OPENGLUTILS_H_

#include "SDL.h"

void glEnable2D();
void glDisable2D();
GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);

#endif /*OPENGLUTILS_H_*/
