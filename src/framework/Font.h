#ifndef FONT_H_
#define FONT_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include "GL/gl.h"

/** BTW, it is covered by the LGPL  ** Bob Pendleton **/
/** http://www.devolution.com/pipermail/sdl/2004-December/066119.html **/

/** 

  +--------------------------------------+
  + Bob Pendleton: writer and programmer +
  + email: Bob@xxxxxxxxxxxxx             +
  + blog:  www.Stonewolf.net             +
  + web:   www.GameProgrammer.com        +
  +--------------------------------------+

	http://www.oreillynet.com/pub/au/1205

	Edits by Kaolin Fire ( kfire@xxxxxxxx; web: erif.org )
		now takes into account glyph minx so glyphs can overlap as intended
		now takes into account newline character

**/

class Font
{
private:
  static const int minGlyph = ' ';
  static const int maxGlyph = 127;

  static int initCounter;

  typedef struct
  {
    int minx, maxx;
    int miny, maxy;
    int advance;
    SDL_Surface *pic;
    GLuint tex;
    GLfloat texMinX, texMinY;
    GLfloat texMaxX, texMaxY;
  } glyph;

  int height;
  int ascent;
  int descent;
  int lineSkip;
  glyph glyphs[maxGlyph + 1];

  const char *fontName;
  int pointSize;
  float fgRed, fgGreen, fgBlue;

  TTF_Font *ttfFont;

  SDL_Color foreground;

public:

  Font(const char *fontName,
       int pointSize, 
       float fgRed, float fgGreen, float fgBlue);

  ~Font();

  void initFont();

  int getLineSkip();

  int getHeight();

  void textSize(char *text, SDL_Rect *r);

  void drawText(const char *text, int x, int y, bool centered = false, bool upsidedown=false);
  void drawText(const char *text, int x, int y,float r, float g, float b);
  void setRGB(float r, float g, float b) { fgRed = r; fgGreen=g, fgBlue=b; };

};

#endif /*FONT_H_*/
