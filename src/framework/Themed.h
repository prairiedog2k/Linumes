#ifndef THEMED_H_
#define THEMED_H_

#include "Theme.h"

class Themed
{
protected:
  Theme *_theme;
public:
	Themed() : _theme(0){};
	Themed(const Themed &themed): _theme(themed._theme) {};
	virtual ~Themed();
	
	Theme *getTheme() { return _theme; };
	virtual void setTheme(Theme *theTheme) { _theme = theTheme; };
};

#endif /*THEMED_H_*/
