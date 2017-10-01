#include "ScreenSaverMode.h"
#include "GameBoardScreenSaver.h"
#include <string>
#include "ModeTypes.h"
ScreenSaverMode::ScreenSaverMode() : GameMode(), _expire(100), _start( SDL_GetTicks())
{
    name=SCREENSAVER_MODE;
    
}

ScreenSaverMode::~ScreenSaverMode()
{
    
}

void ScreenSaverMode::createGameBoard() {
	gameboard = new GameBoardScreenSaver(0.270f,16,12);
}

bool ScreenSaverMode::init() {
	bool bRetVal = GameMode::init();
	gameboard->toggleScanner(_currentTick);
	return bRetVal;
}

void ScreenSaverMode::handleKeyUp( SDL_keysym *keysym ) {
	if ( ( SDL_GetTicks() - _start) >  _expire) {
		modeComplete = true;
	} else {
		GameMode::handleKeyUp(keysym);
	}
}

void ScreenSaverMode::handleKeyDown( SDL_keysym *keysym ) {
	// do nothing
}

