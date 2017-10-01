#ifndef FADINGFOREGROUND_H_
#define FADINGFOREGROUND_H_

#include "SimpleBackground.h"
#include "SDL.h"
#include "framework/TimeLimited.h"
#include "framework/Themed.h"

typedef enum { FADE_IN, FADE_OUT} Fade;

class FadingForeground : public SimpleBackground, public TimeLimited
{	
private:
	Fade _fade;	
	std::string _displayInfo;

	unsigned int _displayDuration;
	unsigned int _displayTimeBegin;
	
	void drawDisplayInfo();
	
public:
	FadingForeground(float x, float y, unsigned int duration);
	
	virtual ~FadingForeground();
	virtual void Draw();
	
	void setFade(Fade fade) { _fade = fade; };
	
	void setDisplayInfo( std::string displayInfo) { _displayTimeBegin = SDL_GetTicks(); _displayInfo = displayInfo; };
	
};

#endif /*FADINGFOREGROUND_H_*/
