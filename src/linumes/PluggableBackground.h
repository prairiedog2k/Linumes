#ifndef PLUGGABLEBACKGROUND_H_
#define PLUGGABLEBACKGROUND_H_

#include "BackgroundTemplate.h"
#include "framework/Theme.h"

class PluggableBackground : public BackgroundTemplate
{
	BackgroundTemplate *_background;
	Theme *_theme;	
	bool hasTemplate;
public:
	PluggableBackground();
	virtual ~PluggableBackground();
  virtual void setTheme(Theme *theme);
  virtual void init();
  virtual void release();
	virtual void Draw();
	virtual bool hasAnimation();
	virtual bool isAnimating();
	virtual void startAnimation();
	virtual void stopAnimation();
  virtual void update();
};

#endif /*PLUGGABLEBACKGROUND_H_*/
