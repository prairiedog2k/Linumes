/*
 * LinumesConfigurationMode.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#include "ConfigurationMode.h"

ConfigurationMode::ConfigurationMode(Configuration *configuration) : _configuration(configuration), _configurationBoard(NULL),
_themeManager(NULL)
{
}

ConfigurationMode::~ConfigurationMode() {
	if (NULL != _configurationBoard) {
		delete _configurationBoard;
	}

	if (NULL != _themeManager) {
		delete _themeManager;
	}
}

void ConfigurationMode::handleKeyUp( SDL_keysym *keysym ) {
	switch ( keysym->sym )
	{
	case SDLK_PAGEDOWN:
	case SDLK_DOWN:
		_configurationBoard->Down();
		break;
	case SDLK_PAGEUP:
	case SDLK_UP:
		_configurationBoard->Up();
		break;
	case SDLK_LEFT:
		_configurationBoard->Left();
		break;
	case SDLK_RIGHT:
		_configurationBoard->Right();
		break;
	default:
		break;
	}
	return;
}

void ConfigurationMode::handleKeyDown( SDL_keysym *keysym ) {
	switch ( keysym->sym )
	{
	case SDLK_KP_ENTER:
    case SDLK_RETURN:
    	if (_configurationBoard->canExit()) {
    		modeComplete = true;
    	}
		_configurationBoard->Select();
		break;
	default:
		break;
	}
	return;
}


bool ConfigurationMode::init() {
	if (NULL == _configurationBoard) {
		_configurationBoard = new ConfigurationBoard("default_configuration", _configuration);
	}
	if (NULL == _themeManager) {
		_themeManager = new LinumesThemeManager("themelist.xml");
		if (!_themeManager->init() ) {
			return false;
		}
	} else {

	}
	_configurationBoard->setTheme( _themeManager->getCurrentTheme());
	_configurationBoard->init();
	return true;
}

void ConfigurationMode::update(unsigned int currTick) {
	_configurationBoard->Draw();
}
