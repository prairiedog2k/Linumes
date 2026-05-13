#ifndef GAMEMODE_H_
#define GAMEMODE_H_

#include <memory>
#include "framework/Mode.h"
#include "GameBoard.h"
#include "LinumesThemeManager.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class GameMode : public HF::Mode
{
protected:
	std::unique_ptr<GameBoard> gameboard;
	std::unique_ptr<HF::ThemeManager> _themeManager;
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

} // namespace Hunchback::Linumes

#endif /*GAMEMODE_H_*/
