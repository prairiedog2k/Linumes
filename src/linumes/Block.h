#include "framework/OpenGLHeaders.h"
#include <array>
#include <memory>
/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
 ***************************************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include "framework/Rendered.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"
#include "GamePiece.h"

namespace Linumes {
namespace HF = Hunchback::Framework;

class Block : public HF::Rendered, public HF::Themed {
public:
    Block();
    Block(Block &block);
    Block(const GamePiece *p1,
          const GamePiece *p2,
          const GamePiece *p3,
          const GamePiece *p4);
    ~Block();

    void Draw();
    bool isScoreTarget();
    bool countableMagic();
    bool AllVisible();
    bool AllInvisible();
    bool isWhole();
    bool hasSpecial(int &x, int &y);
    bool InMotion();
    bool AllStopped();
    void setScreenPosition( float x, float y);
    void setBoardPosition( int boardpos) { _boardpos = boardpos; };
    void setDimension( float dim );
    void setStopped(bool inmotion);
    float getX()       { return _x; };
    void setX(const float x);
    float getY()       { return _y; };
    void setY(const float y);
    float getDimension()     { return _dim; };
    int   getBoardPos()  { return _boardpos; };
    GamePiece *pieceAt(int i);

    Block& operator= (const Block& param);
protected:
    std::array<std::unique_ptr<GamePiece>, 4> _pieces;

    int   _boardpos;
    float _x;
    float _y;
    float _dim;
    bool  _whole;
    bool  _inmotion;
    HF::TextureQuad _quad;
    GLuint getTexture(const char *name);
};

} // namespace Linumes

#endif
