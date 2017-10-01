/*
 * LinumesConfigurationMode.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#ifndef LINUMESCONFIGURATIONMODE_H_
#define LINUMESCONFIGURATIONMODE_H_

#include "framework/Mode.h"
#include "framework/Configuration.h"
#include "LinumesThemeManager.h"
#include "ConfigurationBoard.h"

class ConfigurationMode: public Mode {
private:
	Configuration *_configuration;
	ConfigurationBoard *_configurationBoard;
	unsigned int _currentTick;

protected:
	ThemeManager *_themeManager;

public:
	ConfigurationMode(Configuration *configuration);
	virtual ~ConfigurationMode();

	void handleKeyUp( SDL_keysym *keysym );
	void handleKeyDown( SDL_keysym *keysym );
	bool init();
	void update(unsigned int currTick);

};

#endif /* LINUMESCONFIGURATIONMODE_H_ */
