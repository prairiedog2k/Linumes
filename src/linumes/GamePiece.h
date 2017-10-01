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
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include "framework/Rendered.h"
#include "framework/TimePositioned.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"

class GamePiece : public Rendered, public TimePositioned, public Themed
{
public:
  GamePiece();
  GamePiece(float x, float y, float dim, float edge);  
  GamePiece(const GamePiece &piece);
  ~GamePiece();
private:
  float _dim;
  float _edge;
  int   _color;
  bool  _scoreTarget;
  bool  _overlap;
  bool  _scanned;
  float _fallto;
  
  bool  _special;
  bool  _visited;
  bool  _connected;
  float _nexty;

  TextureQuad _quad;
  
  bool hasMask();
protected:  
  GLuint getTexture( const char *name);
  virtual void bindMask();
  virtual void bindStateTexture(); 

public:
  bool setNewColor(bool CanSpecial = false);
  void getInfo (float &x, float &y, float &dim, int &color);
  void setDimension (const float dim) { _dim = dim; };
  void setEdge(const float edge) {_edge = edge; };
  void setSpecial(const bool special ) { _special = special; };
  void setColor( const int color) { _color = color; };
  void setScoreTarget(const bool magic) {_scoreTarget = magic;};
  void setOverlap(const bool overlap) { _overlap = overlap; };
  void setScanned(const bool scanned) { _scanned = scanned; };
  void setScreenMinY(const float fallto)  { _fallto  = fallto;  };
  void setVisited(const bool visited) { _visited = visited; };
  void setConnected(const bool connected) { _connected = connected; };  
  int   getColor() { return _color;};
  float getDimension() { return _dim;};
  float getScreenMinY()    { return _fallto;    };  
  bool  isScoreTarget()     { return _scoreTarget;     };
  bool  isOverlap()   { return _overlap;   };
  bool  isScanned()   { return _scanned;   };
  bool  isSpecial()   { return _special;   };
  bool  isVisited()   { return _visited;   };
  bool  isConnected() { return _connected; };    
  GamePiece& operator= (const GamePiece& param);
  void copyPieceState( GamePiece *param);
  void Draw();
  
  //updates
  void update(unsigned int currTime);  
  void setNextY(float nexty) { _nexty = nexty;};
  float getNextY() { return _nexty; };
  //override
  bool isStopped();
  
  void Dump();
};
#endif
