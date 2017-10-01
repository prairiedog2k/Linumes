#ifndef TIMELIMITEDGAMEBOARD_H_
#define TIMELIMITEDGAMEBOARD_H_

#include "GameBoard.h"
#include "framework/TextureQuad.h"


class TimeLimitedGameBoard : public GameBoard
{
private:
	unsigned int _gameDuration;
	bool _timeOver;
	TextureQuad _quad;
public:
	TimeLimitedGameBoard();
	TimeLimitedGameBoard(unsigned int gameDuration);
	virtual ~TimeLimitedGameBoard();
	virtual void update(unsigned int currTick);
	virtual void reset();	
protected:
	virtual void updateHud();
	virtual void drawContents();
	virtual void checkHighScore();	
	virtual void evaluateBonus() { }; //do not evaluate bonus
};

#endif /*TIMELIMITEDGAMEBOARD_H_*/
