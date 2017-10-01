#ifndef GAMEMODE_H_
#define GAMEMODE_H_

#include "framework/Mode.h"
#include "GameBoard.h"
#include "LinumesThemeManager.h"

class GameMode : public Mode
{
protected:
	GameBoard *gameboard;
	ThemeManager *_themeManager;
	unsigned int _currentTick;
	virtual void createGameBoard();
public:
	GameMode();
	virtual ~GameMode();
	virtual void handleKeyUp( SDL_keysym *keysym );
	virtual void handleKeyDown( SDL_keysym *keysym );
	virtual bool init();
	virtual void update(unsigned int currTick);
};

#endif /*GAMEMODE_H_*/
