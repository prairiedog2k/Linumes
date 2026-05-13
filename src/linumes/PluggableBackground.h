#ifndef PLUGGABLEBACKGROUND_H_
#define PLUGGABLEBACKGROUND_H_

#include "BackgroundTemplate.h"
#include "framework/Theme.h"

namespace Linumes {
namespace HF = Hunchback::Framework;

class PluggableBackground : public BackgroundTemplate
{
	BackgroundTemplate *_background;
	HF::Theme *_theme;
	bool hasTemplate;
public:
	PluggableBackground();
	virtual ~PluggableBackground();
  virtual void setTheme(HF::Theme *theme);
  virtual void init();
  virtual void release();
	virtual void Draw();
	virtual bool hasAnimation();
	virtual bool isAnimating();
	virtual void startAnimation();
	virtual void stopAnimation();
  virtual void update();
};

} // namespace Linumes

#endif /*PLUGGABLEBACKGROUND_H_*/
