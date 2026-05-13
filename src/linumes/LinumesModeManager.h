#ifndef LINUMESMODEMANAGER_H_
#define LINUMESMODEMANAGER_H_

#include "framework/ModeManager.h"
#include "framework/Mode.h"
#include <map>
#include <string>

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class LinumesModeManager : public HF::ModeManager
{
private:
    void updateCurrentMode();
    void configureSelectedMode(std::pair<std::string, std::map<std::string,std::string> >  selection);

protected:
  virtual void update();
  virtual bool initContext();
  virtual void handleKeyUp( SDL_Keysym *keysym );
  virtual void handleKeyDown( SDL_Keysym *keysym );

public:
	LinumesModeManager();
	LinumesModeManager(std::string configurationFile);
	virtual ~LinumesModeManager();
};

} // namespace Hunchback::Linumes

#endif /*LINUMESMODEMANAGER_H_*/
