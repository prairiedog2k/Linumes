#pragma once

#include "GameMode.h"

namespace Hunchback::Linumes {

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

} // namespace Hunchback::Linumes
