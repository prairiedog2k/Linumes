#pragma once

#include <string>
#include "SDL.h"

namespace Hunchback::Framework {

class Mode
{
protected:
    std::string name;
    bool done;
    bool modeComplete;
public:
	Mode();
	Mode( std::string modename): name(modename), done(false), modeComplete(false) {};
	virtual ~Mode();
    virtual void handleKeyUp( SDL_Keysym *keysym ) = 0;
    virtual void handleKeyDown( SDL_Keysym *keysym ) = 0;
    virtual bool init() = 0;
    virtual void update(unsigned int currtick) = 0;

    std::string getModeName() const { return name;};
    bool isDone()            const { return done; };
    bool isModeComplete()    const { return modeComplete; };

};

} // namespace Hunchback::Framework
