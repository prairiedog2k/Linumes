/*
 * LinumesConfigurationMode.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#ifndef LINUMESCONFIGURATIONMODE_H_
#define LINUMESCONFIGURATIONMODE_H_

#include <memory>
#include "framework/Mode.h"
#include "framework/Configuration.h"
#include "LinumesThemeManager.h"
#include "ConfigurationBoard.h"

class ConfigurationMode: public Mode {
private:
	Configuration *_configuration;
	std::unique_ptr<ConfigurationBoard> _configurationBoard;
	unsigned int _currentTick;

protected:
	std::unique_ptr<ThemeManager> _themeManager;

public:
	ConfigurationMode(Configuration *configuration);
	virtual ~ConfigurationMode();

	void handleKeyUp( SDL_Keysym *keysym );
	void handleKeyDown( SDL_Keysym *keysym );
	bool init();
	void update(unsigned int currTick);

};

#endif /* LINUMESCONFIGURATIONMODE_H_ */
