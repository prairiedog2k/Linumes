#include "framework/OpenGLHeaders.h"
#ifndef TEXTUREQUAD_H_
#define TEXTUREQUAD_H_

namespace Hunchback::Framework {

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
    GLfloat getZ()  const { return _z; };
    GLfloat getX0() const { return _x0; };
    GLfloat getX1() const { return _x1; };
    GLfloat getY0() const { return _y0; };
    GLfloat getY1() const { return _y1; };

    void setDimensionAndPosition2D( GLfloat x, GLfloat y, GLfloat dim);
};

} // namespace Hunchback::Framework

#endif
