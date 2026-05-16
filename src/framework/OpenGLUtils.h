#include "framework/OpenGLHeaders.h"
#pragma once

#include "SDL.h"

namespace Hunchback::Framework {

void glEnable2D();
void glDisable2D();
GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);

} // namespace Hunchback::Framework
