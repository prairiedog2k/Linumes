/*
 * LinumesConfigurationMode.h
 */

#ifndef LINUMESCONFIGURATIONMODE_H_
#define LINUMESCONFIGURATIONMODE_H_

#include <memory>
#include "framework/Mode.h"
#include "framework/Configuration.h"
#include "LinumesThemeManager.h"
#include "ConfigurationBoard.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class ConfigurationMode: public HF::Mode {
private:
	HF::Configuration *_configuration;
	std::unique_ptr<ConfigurationBoard> _configurationBoard;
	unsigned int _currentTick;

protected:
	std::unique_ptr<HF::ThemeManager> _themeManager;

public:
	ConfigurationMode(HF::Configuration *configuration);
	virtual ~ConfigurationMode();

	void handleKeyUp( SDL_Keysym *keysym );
	void handleKeyDown( SDL_Keysym *keysym );
	bool init();
	void update(unsigned int currTick);

};

} // namespace Hunchback::Linumes

#endif /* LINUMESCONFIGURATIONMODE_H_ */
