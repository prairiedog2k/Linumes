#include "LinumesThemeManager.h"

LinumesThemeManager::LinumesThemeManager(std::string file) : ThemeManager(file) {
}

LinumesThemeManager::~LinumesThemeManager()
{
	if (_highScoreManager) {
		_highScoreManager->release();
	}
}

bool LinumesThemeManager::init() {
	bool bRetVal = false;
	if (ThemeManager::init()) {
		_highScoreManager = std::make_unique<HighScoreManager>(_baseTheme.get());
		_highScoreManager->init();
		bRetVal = true;
	}
	return bRetVal;
}
