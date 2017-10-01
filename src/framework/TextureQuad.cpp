#include "TextureQuad.h"

TextureQuad::TextureQuad() : _x0(0.0), _x1(1.0), _y0(0.0), _y1(1.0), _z(1.0) {
}

TextureQuad::TextureQuad(GLfloat x0, GLfloat x1, GLfloat y0, GLfloat y1, GLfloat z) : _x0(x0), _x1(x1), _y0(y0), _y1(y1), _z(z) {
}

TextureQuad::TextureQuad(GLfloat x, GLfloat y, GLfloat dim, GLfloat z) {
    GLfloat halfdim = dim/2.0f;
    _x0 = x - halfdim;
    _x1 = x + halfdim;
    _y0 = y - halfdim;
    _y1 = y + halfdim;
    _z = z;
} 

void TextureQuad::Draw() {
    Draw(getX0(),getX1(),getY0(),getY1(), getZ());
}

void TextureQuad::Draw(GLfloat x0, GLfloat x1, GLfloat y0, GLfloat y1, GLfloat z) {
    glBegin(GL_QUADS);
	    // Bottom Left Of The Texture and Quad
	    glTexCoord2f( 0.0f, 1.0f );
	    glVertex3f( x0, y0, z );
	    // Bottom Right Of The Texture and Quad
	    glTexCoord2f( 1.0f, 1.0f );
	    glVertex3f(  x1, y0, z );
	    // Top Right Of The Texture and Quad
	    glTexCoord2f( 1.0f, 0.00f );
	    glVertex3f(  x1, y1 , z );
	    // Top Left Of The Texture and Quad
	    glTexCoord2f( 0.00f, 0.00f );
	    glVertex3f( x0,  y1, z);
    glEnd();
}

void TextureQuad::Draw(GLfloat x, GLfloat y, GLfloat dim, GLfloat z) {
    Draw(x - (dim /2.0f), x + (dim /2.0f), y - (dim/2.0f), y + (dim/2.0f), z);
}

void TextureQuad::setDimensionAndPosition2D ( GLfloat x, GLfloat y, GLfloat dim) {
    GLfloat halfdim = dim/2.0f;
    _x0 = x - halfdim;
    _x1 = x + halfdim;
    _y0 = y - halfdim;
    _y1 = y + halfdim;
}
