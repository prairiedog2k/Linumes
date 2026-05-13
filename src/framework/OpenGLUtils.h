#include "framework/OpenGLHeaders.h"
#ifndef OPENGLUTILS_H_
#define OPENGLUTILS_H_

#include "SDL.h"

namespace Hunchback::Framework {

void glEnable2D();
void glDisable2D();
GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);

} // namespace Hunchback::Framework

#endif /*OPENGLUTILS_H_*/
