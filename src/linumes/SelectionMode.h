#ifndef SELECTIONMODE_H_
#define SELECTIONMODE_H_

#include "framework/Mode.h"
#include "LinumesThemeManager.h"
#include "SelectionBoard.h"
#include <map>

class SelectionMode : public Mode
{
protected:
	ThemeManager *_themeManager;
private:
	SelectionBoard *_selectionBoard;
	unsigned int _currentTick;
	

	
public:
	SelectionMode();
	virtual ~SelectionMode();
	
	void handleKeyUp( SDL_keysym *keysym );
	void handleKeyDown( SDL_keysym *keysym );
	bool init();
	void update(unsigned int currTick);		
	
	std::pair<std::string, std::map<std::string,std::string> > getSelection();
};

#endif /*SELECTIONMODE_H_*/
