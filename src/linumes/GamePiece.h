/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
 ***************************************************************************/
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include "framework/Rendered.h"
#include "framework/TimePositioned.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class GamePiece : public HF::Rendered, public HF::TimePositioned, public HF::Themed
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

  HF::TextureQuad _quad;

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
  int   getColor()      const { return _color;};
  float getDimension()  const { return _dim;};
  float getScreenMinY() const { return _fallto;    };
  bool  isScoreTarget() const { return _scoreTarget;     };
  bool  isOverlap()     const { return _overlap;   };
  bool  isScanned()     const { return _scanned;   };
  bool  isSpecial()     const { return _special;   };
  bool  isVisited()     const { return _visited;   };
  bool  isConnected()   const { return _connected; };
  GamePiece& operator= (const GamePiece& param);
  void copyPieceState( GamePiece *param);
  void Draw();

  //updates
  void update(unsigned int currTime);
  void setNextY(float nexty) { _nexty = nexty;};
  float getNextY() const { return _nexty; };
  //override
  bool isStopped() const;

  void Dump();
};

} // namespace Hunchback::Linumes

#endif
