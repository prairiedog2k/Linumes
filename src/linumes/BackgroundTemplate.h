#ifndef BACKGROUND_TEMPLATE_H
#define BACKGROUND_TEMPLATE_H

#include "framework/Theme.h"

class BackgroundTemplate;

// the types of the class factories
typedef BackgroundTemplate* create_t();
typedef void destroy_t(BackgroundTemplate *);


class BackgroundTemplate {
public:
  BackgroundTemplate() {};
  virtual ~BackgroundTemplate() {};
  virtual void setTheme(Theme *theme) = 0;
  virtual void init() = 0;
  virtual void release() = 0;
	virtual void Draw() = 0;
	virtual bool hasAnimation() = 0;
	virtual bool isAnimating()= 0;
	virtual void startAnimation() = 0;
	virtual void stopAnimation() = 0;
  virtual void update() = 0;
};

#endif /*BACKGROUND_*/
