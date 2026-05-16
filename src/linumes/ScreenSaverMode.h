#pragma once

#include "GameMode.h"

namespace Hunchback::Linumes {

class ScreenSaverMode : public GameMode
{
private:
	unsigned int _expire;
	unsigned int _start;
protected:
  virtual void createGameBoard();
public:
	ScreenSaverMode();
	virtual ~ScreenSaverMode();
	virtual bool init();
	virtual void handleKeyUp( SDL_Keysym *keysym );
	virtual void handleKeyDown( SDL_Keysym *keysym );

};

} // namespace Hunchback::Linumes
