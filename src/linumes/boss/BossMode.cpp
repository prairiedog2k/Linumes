#include "BossMode.h"
#include "BossModeTypes.h"
#include "BossBoard.h"

BossMode::BossMode() : GameMode()
{
	_themeManager = NULL;
	name = BOSS_MODE;
	_currentTick = SDL_GetTicks();
}

BossMode::~BossMode()
{
}

void BossMode::createGameBoard() {
	gameboard = new BossBoard();
}
