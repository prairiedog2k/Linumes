#ifndef LINUMESMODEMANAGER_H_
#define LINUMESMODEMANAGER_H_

#include "framework/ModeManager.h"
#include "framework/Mode.h"
#include <map>
#include <string>

class LinumesModeManager : public ModeManager
{
private:
    void updateCurrentMode();
    void configureSelectedMode(std::pair<std::string, std::map<std::string,std::string> >  selection);
    
protected:
  virtual void update();
  virtual bool initContext(); 
  virtual void handleKeyUp( SDL_keysym *keysym );
  virtual void handleKeyDown( SDL_keysym *keysym );  	
  
public:
	LinumesModeManager();
	LinumesModeManager(std::string configurationFile);
	virtual ~LinumesModeManager();
};

#endif /*LINUMESMODEMANAGER_H_*/
