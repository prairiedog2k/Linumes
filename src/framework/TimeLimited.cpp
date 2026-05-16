#include "TimeLimited.h"
#include "SDL.h"

namespace Hunchback::Framework {

TimeLimited::TimeLimited(unsigned int duration) : _startTime(0), _duration(duration)
{
}

TimeLimited::~TimeLimited()
{
}

void TimeLimited::start() { 
	_startTime = SDL_GetTicks();
}

float TimeLimited::getPercentComplete() const {
	if (!isComplete() && _duration != 0) {
		float currTime = static_cast<float>(SDL_GetTicks());
		float startTime = static_cast<float>(_startTime);
		float maxTime = static_cast<float>(_duration);
		return ( (currTime - startTime) / maxTime) > 1.0f ? 1.0f : ((currTime - startTime) / maxTime);   
	}
	return 1.0f;
}

bool TimeLimited::isComplete() const {
	if (_startTime > 0) {
		return (SDL_GetTicks() - _startTime) >= _duration;
	}
	return false;
}


} // namespace Hunchback::Framework