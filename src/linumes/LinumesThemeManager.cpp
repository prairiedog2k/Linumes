#include "LinumesThemeManager.h"


namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


LinumesThemeManager::LinumesThemeManager(std::string file) : HF::ThemeManager(file) {
}

LinumesThemeManager::~LinumesThemeManager()
{
	if (_highScoreManager) {
		_highScoreManager->release();
	}
}

bool LinumesThemeManager::init() {
	bool bRetVal = false;
	if (HF::ThemeManager::init()) {
		_highScoreManager = std::make_unique<HighScoreManager>(_baseTheme.get());
		_highScoreManager->init();
		bRetVal = true;
	}
	return bRetVal;
}


} // namespace Hunchback::Linumes