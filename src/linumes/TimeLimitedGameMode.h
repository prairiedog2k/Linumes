#ifndef TIMELIMITEDGAMEMODE_H_
#define TIMELIMITEDGAMEMODE_H_

#include "GameMode.h"

class TimeLimitedGameMode : public GameMode
{
private:
    int _duration;
protected:
	virtual void createGameBoard();
	
public:
	TimeLimitedGameMode();
	TimeLimitedGameMode(int duration);
	virtual ~TimeLimitedGameMode();
};

#endif /*TIMELIMITEDGAMEMODE_H_*/
