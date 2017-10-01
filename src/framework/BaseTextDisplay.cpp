#include "BaseTextDisplay.h"
#include "MediaManager.h"
#include "Utils.h"

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
		float relativeX = ((float)(x) ) / ( 100.0f) * ((float)( MediaManager::getScreenWidth() ));
		return (int)(relativeX);
	}
}
int BaseTextDisplay::getY() { 
	if (!_isRelative ) {
		return xformY(y); 
	} else {
		float relativeY = ((float)(y) ) / ( 100.0f) * ((float)( MediaManager::getScreenHeight() ));
		return (int)(relativeY);
	}
}


