/*
 * LinumesConfigurationBoard.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#include "ConfigurationBoard.h"
#include "SelectionTypes.h"
#include "framework/ResourceHelper.h"
#include "framework/Utils.h"

ConfigurationBoard::ConfigurationBoard(std::string name, Configuration *configuration) :
	SelectionBoard(name),
	_optionMode(false),
	_configuration(configuration)
{

}

ConfigurationBoard::~ConfigurationBoard() {

}

bool ConfigurationBoard::isOptionMode() {
	return _optionMode;
}

void ConfigurationBoard::setOptionMode(bool mode) {
	_optionMode = mode;
}


std::string ConfigurationBoard::getSelectionResource() {
	return CFG_SELECTIONS;
}

void ConfigurationBoard::init() {
	SelectionBoard::init();
	setOptionMode(false);
	updateOptions();
}

void ConfigurationBoard::alignSelectionsWithConfiguration() {

}

void ConfigurationBoard::updateOptions() {
	_currentOption = _currentOptions.begin();
	while (_currentOption != _currentOptions.end()) {
		if ( (*_currentOption).value ==
				_configuration->getValue(getSelection().name))  {
			return;
		}
		_currentOption++;
	}
	if (_currentOption == _currentOptions.end()) {
		_currentOption = _currentOptions.begin();
	}
}

void ConfigurationBoard::Up() {
	if (! isOptionMode()) {
		SelectionBoard::Up();
		updateOptions();
	} else {
		if (_currentOption == _currentOptions.begin()) {
			_currentOption = _currentOptions.end();
		}
		_currentOption--;
	}
}

void ConfigurationBoard::Down() {
	if (! isOptionMode()) {
		SelectionBoard::Down();
		updateOptions();
	} else {
		_currentOption++;
		if (_currentOption == _currentOptions.end()) {
			_currentOption = _currentOptions.begin();
		}
	}
}

void ConfigurationBoard::Left() {

}

void ConfigurationBoard::Right() {

}

void ConfigurationBoard::Select() {
	if (! isOptionMode()) {
		setOptionMode(true);
	} else {
		_configuration->set(getSelection().name,(*_currentOption).value);
		setOptionMode(false);
	}
}

void ConfigurationBoard::update(unsigned int currentTime) {

}

std::string ConfigurationBoard::getSelectionsTitle() {
	return "C o n f i g u r a t i o n";
}

bool ConfigurationBoard::isCurrentOptionValue(std::string value) {
		return value == (*_currentOption).value;
}

void ConfigurationBoard::drawOptions() {
	Font *f0 = ResourceHelper::getFontResource(getTheme(), LINUMES_FONT_72)->getResource();
	f0->setRGB(0.0f,0.0f,0.0f);
	f0->drawText(getSelection().display.c_str(), xformX(513), xformY(619), true);
	f0->setRGB(1.0f,1.0f,1.0f);
	f0->drawText(getSelection().display.c_str(), xformX(512), xformY(620), true);

	Font *f1 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_24 )->getResource();
	int ypos = 500;
	for (std::list< Option >::iterator iter = _currentOptions.begin();
			iter != _currentOptions.end(); iter++)
	{
		f1->setRGB(0.0f,0.0f,0.0f);
		f1->drawText((*iter).display.c_str(), xformX(513), xformY(ypos-1), true);
		if  ( isCurrentOptionValue( (*iter).value ) ) {
			f1->setRGB(1.0f,0.0f,0.0f);
		} else {
			f1->setRGB(1.0f,1.0f,1.0f);
		}
		f1->drawText((*iter).display.c_str(), xformX(512), xformY(ypos), true);
		ypos -= 75;
	}
}

void ConfigurationBoard::drawAdditional() {
	if ( ! isOptionMode()) {
		SelectionBoard::drawAdditional();
	} else {
		drawOptions();
	}
}
