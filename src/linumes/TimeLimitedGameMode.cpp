#include "TimeLimitedGameMode.h"
#include "TimeLimitedGameBoard.h"

#include "ModeTypes.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


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
	gameboard = std::make_unique<TimeLimitedGameBoard>(_duration);
}


} // namespace Hunchback::Linumes