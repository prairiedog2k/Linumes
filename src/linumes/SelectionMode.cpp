#include <memory>
#include "SelectionMode.h"
#include "ModeTypes.h"


namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


SelectionMode::SelectionMode(): HF::Mode(SELECTION_MODE)
{
	_currentTick = SDL_GetTicks();
}

SelectionMode::~SelectionMode() = default;

std::pair<std::string, std::map<std::string,std::string> > SelectionMode::getSelection() {
    return _selectionBoard->getSelectionDisplayAndParameters();
}

void SelectionMode::handleKeyUp( SDL_Keysym *keysym ) {
	switch ( keysym->sym )
	{
	case SDLK_PAGEDOWN:
	case SDLK_DOWN:
		_selectionBoard->Down();
		break;
	case SDLK_PAGEUP:
	case SDLK_UP:
		_selectionBoard->Up();		  
		break;

	default:
		break;
	}
	return;
}
void SelectionMode::handleKeyDown( SDL_Keysym *keysym ) {
	switch ( keysym->sym )
	{
	case SDLK_KP_ENTER:
    case SDLK_RETURN:
    	if (_selectionBoard->canExit()) {
			done = true;
    	} else {
    		modeComplete = true;
    	}
        break;
	default:
		break;
	}
	return;

}
bool SelectionMode::init() {
	_selectionBoard = std::make_unique<SelectionBoard>("defaultSelection");

	if (!_themeManager) {
		_themeManager = std::make_unique<LinumesThemeManager>("resources/themelist.yaml");
		if (!_themeManager->init()) {
			return false;
		}
	}
	_selectionBoard->setTheme(_themeManager->getCurrentTheme());
	_selectionBoard->init();
	return true;
}

void SelectionMode::update(unsigned int currTick) {
	_selectionBoard->Draw();
}


} // namespace Hunchback::Linumes