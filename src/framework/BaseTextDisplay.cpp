#include "BaseTextDisplay.h"
#include "MediaManager.h"
#include "Utils.h"

namespace Hunchback::Framework {

BaseTextDisplay::BaseTextDisplay() : _hasDrop(false), _isRelative(false)
{
}

BaseTextDisplay::~BaseTextDisplay()
{
}

std::string BaseTextDisplay::getFormattedText() {
				std::ostringstream strout;
		  	strout << baseText << value << std::endl;
		  	return strout.str();
};

int BaseTextDisplay::getX() {
	if (! _isRelative ) {
		return xformX(x);
	} else {
		float relativeX = static_cast<float>(x) / 100.0f * static_cast<float>(MediaManager::getScreenWidth());
		return static_cast<int>(relativeX);
	}
}
int BaseTextDisplay::getY() {
	if (!_isRelative ) {
		return xformY(y);
	} else {
		float relativeY = static_cast<float>(y) / 100.0f * static_cast<float>(MediaManager::getScreenHeight());
		return static_cast<int>(relativeY);
	}
}

} // namespace Hunchback::Framework
