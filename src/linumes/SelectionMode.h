#ifndef SELECTIONMODE_H_
#define SELECTIONMODE_H_

#include <map>
#include <memory>
#include "framework/Mode.h"
#include "LinumesThemeManager.h"
#include "SelectionBoard.h"

namespace Linumes {
namespace HF = Hunchback::Framework;

class SelectionMode : public HF::Mode
{
protected:
	std::unique_ptr<HF::ThemeManager> _themeManager;
private:
	std::unique_ptr<SelectionBoard> _selectionBoard;
	unsigned int _currentTick;



public:
	SelectionMode();
	virtual ~SelectionMode();

	void handleKeyUp( SDL_Keysym *keysym );
	void handleKeyDown( SDL_Keysym *keysym );
	bool init();
	void update(unsigned int currTick);

	std::pair<std::string, std::map<std::string,std::string> > getSelection();
};

} // namespace Linumes

#endif /*SELECTIONMODE_H_*/
