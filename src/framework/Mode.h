#ifndef MODE_H_
#define MODE_H_

#include <string>
#include "SDL.h"

using namespace std;

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
    virtual void handleKeyUp( SDL_keysym *keysym ) = 0;
    virtual void handleKeyDown( SDL_keysym *keysym ) = 0;
    virtual bool init() = 0;
    virtual void update(unsigned int currtick) = 0;
    
    std::string getModeName() { return name;}; 
    bool isDone() { return done; };
    bool isModeComplete() { return modeComplete; };
  
};

#endif /*MODE_H_*/
