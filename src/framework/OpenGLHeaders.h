#pragma once
// On Windows, windows.h must be included before GL/gl.h or WINGDIAPI/APIENTRY get redefined.
#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

// GL 1.3 texture-combiner constants — not in the Windows SDK gl.h
#ifndef GL_COMBINE
#  define GL_COMBINE          0x8570
#  define GL_COMBINE_RGB      0x8571
#  define GL_COMBINE_ALPHA    0x8572
#  define GL_RGB_SCALE        0x8573
#  define GL_ADD_SIGNED       0x8574
#  define GL_INTERPOLATE      0x8575
#  define GL_CONSTANT         0x8576
#  define GL_PRIMARY_COLOR    0x8577
#  define GL_PREVIOUS         0x8578
#  define GL_SOURCE0_RGB      0x8580
#  define GL_SOURCE1_RGB      0x8581
#  define GL_SOURCE2_RGB      0x8582
#  define GL_OPERAND0_RGB     0x8590
#  define GL_OPERAND1_RGB     0x8591
#  define GL_OPERAND2_RGB     0x8592
#  define GL_SOURCE0_ALPHA    0x8588
#  define GL_SOURCE1_ALPHA    0x8589
#  define GL_OPERAND0_ALPHA   0x8598
#  define GL_OPERAND1_ALPHA   0x8599
#endif

// GL 1.2 packed pixel constants — not in the Windows SDK gl.h
#ifndef GL_BGR
#  define GL_BGR              0x80E0
#  define GL_BGRA             0x80E1
#endif
