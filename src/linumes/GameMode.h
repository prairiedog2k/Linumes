#ifndef GAMEMODE_H_
#define GAMEMODE_H_

#include <memory>
#include "framework/Mode.h"
#include "GameBoard.h"
#include "LinumesThemeManager.h"

class GameMode : public Mode
{
protected:
	std::unique_ptr<GameBoard> gameboard;
	std::unique_ptr<ThemeManager> _themeManager;
	unsigned int _currentTick;
	virtual void createGameBoard();
public:
	GameMode();
	virtual ~GameMode();
	virtual void handleKeyUp( SDL_Keysym *keysym );
	virtual void handleKeyDown( SDL_Keysym *keysym );
	virtual bool init();
	virtual void update(unsigned int currTick);
};

#endif /*GAMEMODE_H_*/
