#include "TimeLimitedGameMode.h"
#include "TimeLimitedGameBoard.h"

#include "ModeTypes.h"
TimeLimitedGameMode::TimeLimitedGameMode() : GameMode(), _duration(60)
{
    name=TIMELIMITED_MODE;
}

TimeLimitedGameMode::TimeLimitedGameMode(int duration) : GameMode(), _duration(duration) {
    name=TIMELIMITED_MODE;
}

TimeLimitedGameMode::~TimeLimitedGameMode()
{
}

void TimeLimitedGameMode::createGameBoard() {
	gameboard = new TimeLimitedGameBoard(_duration); 
}
