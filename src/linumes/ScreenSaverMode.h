#ifndef SCREENSAVERMODE_H_
#define SCREENSAVERMODE_H_

#include "GameMode.h"

namespace Linumes {

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

} // namespace Linumes

#endif /*SCREENSAVERMODE_H_*/
