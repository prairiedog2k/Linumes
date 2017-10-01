#include "GameMode.h"
#include "ModeTypes.h"

GameMode::GameMode() : Mode(), gameboard(NULL) {
	_themeManager = NULL;
	name = GAME_MODE;
	_currentTick = SDL_GetTicks();
}

GameMode::~GameMode()
{
	if (gameboard != NULL) {
		delete gameboard;
	}

	if (_themeManager != NULL) {
		delete _themeManager;
	}
}

void GameMode::createGameBoard() {
	gameboard = new GameBoard(0.2f,16,10);	
}

bool GameMode::init() {
	createGameBoard();

	if (NULL == _themeManager) {
		_themeManager = new LinumesThemeManager("themelist.xml");
		if (!_themeManager->init() ) {
			return false;
		}
	}

	gameboard->setThemeManager( dynamic_cast<LinumesThemeManager *>(_themeManager));

	gameboard->init();
	//stop until ready to start
	gameboard->toggleScanner(_currentTick);
	return true;
}

void GameMode::update(unsigned int currTick) {
	_currentTick = currTick;
	gameboard->update(currTick);
	gameboard->Draw();
}

/* function to handle key press events */
void GameMode::handleKeyUp( SDL_keysym *keysym )
{
	switch ( keysym->sym )
	{
	case SDLK_LEFT:
		gameboard->LeftKeyUp();
		break;
	case SDLK_RIGHT:
		gameboard->RightKeyUp();
		break;
	case SDLK_DOWN:
		gameboard->DownKeyUp();
		break;
	case SDLK_UP:
		break;
	case SDLK_t:
		break;
	case SDLK_z:
		break;
	default:
		break;
	}
	return;
}

/* function to handle key press events */
void GameMode::handleKeyDown( SDL_keysym *keysym )
{
	switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
		/* ESC key was pressed */
		done = true;
		break;
	case SDLK_BACKSPACE:
		if (gameboard->isGameOver()) {
			modeComplete = true;
		}
		break;
	case SDLK_KP_ENTER:		
	case SDLK_RETURN: 
		if (gameboard->isGameOver()) {
			//reset
			gameboard->reset();
		} else {
			//pause
			gameboard->toggleScanner(_currentTick);
		}
		break;
	case SDLK_LEFT:
		gameboard->LeftKeyDown();
		break;
	case SDLK_RIGHT:
		gameboard->RightKeyDown();
		break;
	case SDLK_DOWN:
		gameboard->DownKeyDown();
		break;
	case SDLK_UP:
		break;
	case SDLK_m:
		gameboard->changeTheme();
		break;
	case SDLK_b:
		gameboard->dump();
		break;
	case SDLK_z:
		gameboard->RotateLeft();
		break;
	case SDLK_x:
		gameboard->RotateRight();
		break;
	case SDLK_a:
		gameboard->advanceToken();
		break;    
	default:
		break;
	}
	return;
}



