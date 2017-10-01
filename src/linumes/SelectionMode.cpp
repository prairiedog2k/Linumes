#include "SelectionMode.h"
#include "ModeTypes.h"

SelectionMode::SelectionMode(): Mode(SELECTION_MODE), _themeManager(NULL),  _selectionBoard(NULL) 
{
    
	_currentTick = SDL_GetTicks();
}

SelectionMode::~SelectionMode()
{
	if (NULL != _selectionBoard) {
		delete _selectionBoard;
	}
	if (NULL != _themeManager) {
		delete _themeManager;
	}
}

std::pair<std::string, std::map<std::string,std::string> > SelectionMode::getSelection() {
    return _selectionBoard->getSelectionDisplayAndParameters();
}

void SelectionMode::handleKeyUp( SDL_keysym *keysym ) {
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
void SelectionMode::handleKeyDown( SDL_keysym *keysym ) {
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
	
	_selectionBoard  = new SelectionBoard("defaultSelection");
	
	if (NULL == _themeManager) {
		_themeManager = new LinumesThemeManager("themelist.xml");
		if (!_themeManager->init() ) {
			return false;
		}
	}
	_selectionBoard->setTheme( _themeManager->getCurrentTheme());
	_selectionBoard->init();
	return true;
}

void SelectionMode::update(unsigned int currTick) {
	_selectionBoard->Draw();
}
