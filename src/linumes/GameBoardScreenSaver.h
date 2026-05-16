#pragma once

#include "GameBoard.h"

namespace Hunchback::Linumes {

class GameBoardScreenSaver: public GameBoard
{
protected:
  void jumbleBlocks();
  int scanTo(int column);
  //void cleanScanned(int column);
  void resetScan();
  void markScoreTargets();
  virtual void Draw();
  virtual void toggleVisible();
public:
	GameBoardScreenSaver( float dim, int rx, int ry);
	virtual ~GameBoardScreenSaver();
	virtual void toggleScanner(unsigned int currTime);
	virtual void update(unsigned int currTime);
	virtual void init();

};

} // namespace Hunchback::Linumes
