#ifndef THEMED_H_
#define THEMED_H_

#include "Theme.h"

namespace Hunchback::Framework {

class Themed
{
protected:
  Theme *_theme;
public:
	Themed() : _theme(0){};
	Themed(const Themed &themed): _theme(themed._theme) {};
	virtual ~Themed();

	Theme *getTheme() const { return _theme; };
	virtual void setTheme(Theme *theTheme) { _theme = theTheme; };
};

} // namespace Hunchback::Framework

#endif /*THEMED_H_*/
