/*
 * LinumesConfigurationMode.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#include <memory>
#include "ConfigurationMode.h"


namespace Linumes {
namespace HF = Hunchback::Framework;


ConfigurationMode::ConfigurationMode(HF::Configuration *configuration) : _configuration(configuration)
{
}

ConfigurationMode::~ConfigurationMode() = default;

void ConfigurationMode::handleKeyUp( SDL_Keysym *keysym ) {
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

void ConfigurationMode::handleKeyDown( SDL_Keysym *keysym ) {
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
	if (!_configurationBoard) {
		_configurationBoard = std::make_unique<ConfigurationBoard>("default_configuration", _configuration);
	}
	if (!_themeManager) {
		_themeManager = std::make_unique<LinumesThemeManager>("themelist.yaml");
		if (!_themeManager->init()) {
			return false;
		}
	}
	_configurationBoard->setTheme(_themeManager->getCurrentTheme());
	_configurationBoard->init();
	return true;
}

void ConfigurationMode::update(unsigned int currTick) {
	_configurationBoard->Draw();
}


} // namespace Linumes