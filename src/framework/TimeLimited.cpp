#include "TimeLimited.h"
#include "SDL.h"
TimeLimited::TimeLimited(unsigned int duration) : _startTime(0), _duration(duration)
{
}

TimeLimited::~TimeLimited()
{
}

void TimeLimited::start() { 
	_startTime = SDL_GetTicks();
}

float TimeLimited::getPercentComplete() {
	if (!isComplete() && _duration != 0) {
		float currTime = (float)SDL_GetTicks();
		float startTime = (float)_startTime;
		float maxTime = (float)_duration;
		return ( (currTime - startTime) / maxTime) > 1.0f ? 1.0f : ((currTime - startTime) / maxTime);   
	}
	return 1.0f;
}

bool TimeLimited::isComplete() {
	if (_startTime > 0) {
		return (SDL_GetTicks() - _startTime) >= _duration;
	}
	return false;
}
