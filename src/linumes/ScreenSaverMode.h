#ifndef SCREENSAVERMODE_H_
#define SCREENSAVERMODE_H_

#include "GameMode.h"

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
	virtual void handleKeyUp( SDL_keysym *keysym );
	virtual void handleKeyDown( SDL_keysym *keysym );
	
};

#endif /*SCREENSAVERMODE_H_*/
