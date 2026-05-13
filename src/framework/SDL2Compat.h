#pragma once
// SDL1 -> SDL2 compatibility shims force-included on MSVC builds
#include "SDL.h"

// SDL_DisplayFormatAlpha was removed in SDL2; map to the SDL2 equivalent
#ifndef SDL_DisplayFormatAlpha
#define SDL_DisplayFormatAlpha(s) SDL_ConvertSurfaceFormat((s), SDL_PIXELFORMAT_ARGB8888, 0)
#endif
