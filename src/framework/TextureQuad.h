#ifndef TEXTUREQUAD_H_
#define TEXTUREQUAD_H_

#include <GL/gl.h>

class TextureQuad {
private:
    GLfloat _x0;
    GLfloat _x1;
    GLfloat _y0;
    GLfloat _y1;
    GLfloat _z;
public:
    TextureQuad();
    TextureQuad(GLfloat x0, GLfloat x1, GLfloat y0, GLfloat y1, GLfloat z);
    TextureQuad(GLfloat x, GLfloat y, GLfloat dim, GLfloat z);
    
    void Draw();
    void Draw(GLfloat x0, GLfloat x1, GLfloat y0, GLfloat y1, GLfloat z);
    void Draw(GLfloat x, GLfloat y, GLfloat dim, GLfloat z);
    
    void setZ( GLfloat z) { _z = z; };
    GLfloat getZ() { return _z; };
    GLfloat getX0() { return _x0; };
    GLfloat getX1() { return _x1; };
    GLfloat getY0() { return _y0; };
    GLfloat getY1() { return _y1; };
    
    void setDimensionAndPosition2D( GLfloat x, GLfloat y, GLfloat dim);
};

#endif
