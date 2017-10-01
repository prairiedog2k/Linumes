#include "LinumesThemeManager.h"

LinumesThemeManager::LinumesThemeManager(std::string file) : ThemeManager(file), _highScoreManager(NULL) {
	
}


LinumesThemeManager::~LinumesThemeManager()
{
	_highScoreManager->release();
	delete _highScoreManager;
}

bool LinumesThemeManager::init() {
	bool bRetVal = false;
	if (ThemeManager::init()) {
		_highScoreManager = new HighScoreManager(_baseTheme);
		_highScoreManager->init();
		bRetVal = true;
	}
	return bRetVal;
}
