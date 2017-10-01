#include "Font.h"
#include "Utils.h"
#include "OpenGLUtils.h"
#include <string>
#include <iostream>

#ifdef MING_GL
#include "GL/glu.h"
#include "GL/glext.h"
#endif
int Font::initCounter = 0;

Font::Font(const char *fontName,
		int pointSize,
		float fgRed, float fgGreen, float fgBlue):
			fontName(fontName),
			pointSize(pointSize),
			fgRed(fgRed), fgGreen(fgGreen), fgBlue(fgBlue),
			ttfFont(NULL)
			{
	initCounter++;
	initFont();
			}

Font::~Font()
{
	for (int i = minGlyph; i < maxGlyph + 1; i++) {
		if (glyphs[i].pic != NULL) {
			SDL_FreeSurface(glyphs[i].pic);
			glDeleteTextures( 1, & (glyphs[i].tex) );
		}
	}

	initCounter--;
}

void Font::initFont()
{
	ttfFont = TTF_OpenFont(fontName, pointSize);
	
	if (NULL == ttfFont)
	{
		printf("Can't open font file\n");
		//TODO :: errorExit("Can't open font file");
	}

	foreground.r = (Uint8)(255);
	foreground.g  = (Uint8)(255);
	foreground.b = (Uint8)(255);

	height = TTF_FontHeight(ttfFont);
	ascent = TTF_FontAscent(ttfFont);
	descent = TTF_FontDescent(ttfFont);
	lineSkip = TTF_FontLineSkip(ttfFont);

	for (int i = minGlyph; i <= maxGlyph; i++)
	{
		glyphs[i].pic = NULL;
		glyphs[i].tex = 0;
	}

    //pre-load characters
    for (unsigned char c = ' '; c < maxGlyph; c++) {
    	GLfloat texcoord[4];
    	char letter[2] = {0, 0};

		SDL_Surface *g0 = NULL;
		SDL_Surface *g1 = NULL;

		letter[0] = c;

		TTF_GlyphMetrics(ttfFont,
				(Uint16)c,
				&glyphs[((int)c)].minx,
				&glyphs[((int)c)].maxx,
				&glyphs[((int)c)].miny,
				&glyphs[((int)c)].maxy,
				&glyphs[((int)c)].advance);

		g0 = TTF_RenderText_Blended(ttfFont,
				letter,
				foreground);

		if (NULL != g0)
		{
			g1 = SDL_DisplayFormatAlpha(g0);
			SDL_FreeSurface(g0);
		}

		if (NULL != g1)
		{
			glyphs[((int)c)].pic = g1;
			glyphs[((int)c)].tex = SDL_GL_LoadTexture(g1, texcoord);
			glyphs[((int)c)].texMinX = texcoord[0];
			glyphs[((int)c)].texMinY = texcoord[1];
			glyphs[((int)c)].texMaxX = texcoord[2];
			glyphs[((int)c)].texMaxY = texcoord[3];
		}
	}
	
	TTF_CloseFont(ttfFont);
}

int Font::getLineSkip()
{
	return lineSkip;
}

int Font::getHeight()
{
	return height;
}

void Font::textSize(char *text, 
		SDL_Rect *r)
{
	int maxx = 0;
	int advance = 0;
	int w_largest = 0;
	char lastchar = 0;
	r->x = 0;
	r->y = 0;
	r->w = 0;
	r->h = height;

	while (0 != *text)
	{
		if ((minGlyph <= *text) && (*text < maxGlyph))
		{
			lastchar = *text;
			if (*text == '\n') {
				r->h += lineSkip;
				r->w = r->w - advance + maxx;
				if (r->w > w_largest) w_largest = r->w;
				r->w = 0;
			} else {
                maxx = glyphs[((int)*text)].maxx;
				advance = glyphs[((int)*text)].advance;
				r->w += advance;
			}
		}

		text++;
	}
	if (lastchar != '\n') {
		r->w = r->w - advance + maxx;
		if (r->w > w_largest) w_largest = r->w;
	} else {
		r->h -= lineSkip;
	}

	if (w_largest > r->w) r->w = w_largest;

}

void Font::drawText(const char *text, int x, int y, bool centered, bool upsidedown)
{
	glEnable2D();

	GLfloat left, right;
	GLfloat top, bottom;
	GLfloat texMinX, texMinY;
	GLfloat texMaxX, texMaxY;
	GLfloat minx;
	GLfloat baseleft = x;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glEnable(GL_TEXTURE_2D);
	
	if (centered) {
		GLfloat widthX = 0;
		std::string strText(text);
		for (unsigned int i = 0; i < strText.size(); i++) {
			int ch = strText.at(i);
			if ((minGlyph <= ch) && (ch <= maxGlyph) ){
				widthX += glyphs[ch].pic->w;
			}				
		}
		x = (int)(baseleft - (widthX / 2));
	}

	//alpha channel needs help
	GLfloat arr0[4] = { fgRed, fgGreen, fgBlue,1.0f }; 
	
	while (0 != *text) {
		if (*text == '\n') {
			x = (int)baseleft;
			if (upsidedown) {
				y -= lineSkip;
			} else {
				y += lineSkip;
			}
		} else if ((minGlyph <= *text) && (*text < maxGlyph)) {
			texMinX = glyphs[((int)*text)].texMinX;
			texMinY = glyphs[((int)*text)].texMinY;
			texMaxX = glyphs[((int)*text)].texMaxX;
			texMaxY = glyphs[((int)*text)].texMaxY;

			minx = glyphs[((int)*text)].minx;

			left   = x + minx;
			right  = x + glyphs[((int)*text)].pic->w + minx;
			top    = y;
			bottom = y + glyphs[((int)*text)].pic->h;

			glBindTexture(GL_TEXTURE_2D, glyphs[((int)*text)].tex);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_CONSTANT);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
			glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, arr0);
			glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE, 1);
			
			glBegin(GL_TRIANGLE_STRIP);

			glTexCoord2f(texMinX, texMinY); glVertex2f( left,    bottom);
			glTexCoord2f(texMaxX, texMinY); glVertex2f(right,    bottom);
			glTexCoord2f(texMinX, texMaxY); glVertex2f( left, top);
			glTexCoord2f(texMaxX, texMaxY); glVertex2f(right, top);
			
			glEnd();

			x += glyphs[((int)*text)].advance;
		}

		text++;
	}
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();

	glDisable2D();
}

void Font::drawText(const char *text, int x, int y,float r, float g, float b) {
	float tmpR = fgRed;
	float tmpG = fgGreen;
	float tmpB = fgBlue;
	fgRed = r;
	fgGreen = g;
	fgBlue = b;
	drawText(text,x,y);
	fgRed = tmpR;
	fgGreen = tmpG;
	fgBlue = tmpB;
}
