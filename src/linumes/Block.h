/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include "framework/Rendered.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"
#include "GamePiece.h"
#include "GL/gl.h"

using namespace std;
class Block : public Rendered, public Themed {
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
    GamePiece *_pieces[4];

    int   _boardpos;
    float _x;
    float _y;
    float _dim;    
    bool  _whole;
    bool  _inmotion;
    TextureQuad _quad;
    GLuint getTexture(const char *name);
};
#endif
