#include "LinumesModeManager.h"
#include "ScreenSaverMode.h"
#include "GameMode.h"
#include "SelectionMode.h"
#include "TimeLimitedGameMode.h"
#include "boss/BossMode.h"
#include "ConfigurationMode.h"

#include "ModeTypes.h"


namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


LinumesModeManager::LinumesModeManager() : HF::ModeManager()
{
	//do nothing
}

LinumesModeManager::LinumesModeManager(std::string configurationFile) : HF::ModeManager(configurationFile) {
	//do nothing
}

LinumesModeManager::~LinumesModeManager()
{
}

bool LinumesModeManager::initContext() {
	mediamanager->resetGlContext();

    if (!currMode) {
        currMode = std::make_unique<SelectionMode>();
    }

	currMode->init();

	return true;
}

void LinumesModeManager::configureSelectedMode(std::pair<std::string, std::map<std::string,std::string> >  selection) {
    std::map<std::string, std::string> params = selection.second;

    std::string nextMode = params[std::string(PK_MODE)];
    if ( GAME_MODE == nextMode ) {
        currMode = std::make_unique<GameMode>();
    } else if ( SCREENSAVER_MODE == nextMode ) {
        currMode = std::make_unique<ScreenSaverMode>();
    } else if ( TIMELIMITED_MODE == nextMode ) {
        std::string duration = params[std::string(PK_DURATION)];
        int nduration = std::stoi(duration);
        currMode = std::make_unique<TimeLimitedGameMode>(nduration);
    } else if ( BOSS_MODE == nextMode) {
        currMode = std::make_unique<BossMode>();
    } else if ( CONFIG_MODE == nextMode) {
    	currMode = std::make_unique<ConfigurationMode>(&configuration);
    } else {
        currMode = std::make_unique<SelectionMode>();
    }
}

void LinumesModeManager::handleKeyUp( SDL_Keysym *keysym ) {
	currMode->handleKeyUp(keysym);
}

void LinumesModeManager::handleKeyDown( SDL_Keysym *keysym ) {
	switch ( keysym->sym )
	{
	default:
		currMode->handleKeyDown(keysym);
	}
}

void LinumesModeManager::updateCurrentMode() {
		HF::ModeManager::release();
		HF::ModeManager::init();
}

void LinumesModeManager::update() {
	// this is the place where we can switch modes based on what has happened from the last update
	if ( currMode->isModeComplete() ){
        if (currMode->getModeName() == SELECTION_MODE ){
            std::pair<std::string, std::map<std::string,std::string> > selection = (dynamic_cast<SelectionMode *>(currMode.get()))->getSelection();
            configureSelectedMode(selection);
        } else {
            currMode = std::make_unique<SelectionMode>();
        }
        updateCurrentMode();
	}
}


} // namespace Hunchback::Linumes