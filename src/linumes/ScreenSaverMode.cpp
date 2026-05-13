#include "ScreenSaverMode.h"
#include "GameBoardScreenSaver.h"
#include <memory>
#include <string>
#include "ModeTypes.h"

namespace Linumes {
namespace HF = Hunchback::Framework;


ScreenSaverMode::ScreenSaverMode() : GameMode(), _expire(100), _start( SDL_GetTicks())
{
    name=SCREENSAVER_MODE;
    
}

ScreenSaverMode::~ScreenSaverMode()
{
    
}

void ScreenSaverMode::createGameBoard() {
	gameboard = std::make_unique<GameBoardScreenSaver>(0.270f,16,12);
}

bool ScreenSaverMode::init() {
	bool bRetVal = GameMode::init();
	gameboard->toggleScanner(_currentTick);
	return bRetVal;
}

void ScreenSaverMode::handleKeyUp( SDL_Keysym *keysym ) {
	if ( ( SDL_GetTicks() - _start) >  _expire) {
		modeComplete = true;
	} else {
		GameMode::handleKeyUp(keysym);
	}
}

void ScreenSaverMode::handleKeyDown( SDL_Keysym *keysym ) {
	// do nothing
}



} // namespace Linumes