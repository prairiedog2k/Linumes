#include "BossMode.h"
#include "BossModeTypes.h"
#include "BossBoard.h"

BossMode::BossMode() : GameMode()
{
	_themeManager = nullptr;
	name = BOSS_MODE;
	_currentTick = SDL_GetTicks();
}

BossMode::~BossMode()
{
}

void BossMode::createGameBoard() {
	gameboard = std::make_unique<BossBoard>();
}
