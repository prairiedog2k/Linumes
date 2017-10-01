#include "LinumesModeManager.h"
#include "ScreenSaverMode.h"
#include "GameMode.h"
#include "SelectionMode.h"
#include "TimeLimitedGameMode.h"
#include "boss/BossMode.h"
#include "ConfigurationMode.h"

#include "ModeTypes.h"

LinumesModeManager::LinumesModeManager() : ModeManager()
{
	//do nothing
}

LinumesModeManager::LinumesModeManager(std::string configurationFile) : ModeManager(configurationFile) {
	//do nothing
}

LinumesModeManager::~LinumesModeManager()
{
}

bool LinumesModeManager::initContext() {
	mediamanager->resetGlContext();
    
    if (NULL == currMode) {
        currMode = new SelectionMode();
    }
    
	currMode->init();

	return true;
}

void LinumesModeManager::configureSelectedMode(std::pair<std::string, std::map<std::string,std::string> >  selection) {
    std::map<std::string, std::string> params = selection.second;
    
    std::string nextMode = params[std::string(PK_MODE)];
    
    delete currMode;
    
    if ( GAME_MODE == nextMode ) {
        currMode = new GameMode();
    } else if ( SCREENSAVER_MODE == nextMode ) {
        currMode = new ScreenSaverMode();
    } else if ( TIMELIMITED_MODE == nextMode ) {
        std::string duration = params[std::string(PK_DURATION)];
        int nduration = atoi ( duration.c_str() );
        currMode = new TimeLimitedGameMode(nduration);
    } else if ( BOSS_MODE == nextMode) {
        currMode = new BossMode();
    } else if ( CONFIG_MODE == nextMode) {
    	currMode = new ConfigurationMode(&configuration);
    } else {
        currMode = new SelectionMode();
    }       
}

void LinumesModeManager::handleKeyUp( SDL_keysym *keysym ) {
	currMode->handleKeyUp(keysym);
}

void LinumesModeManager::handleKeyDown( SDL_keysym *keysym ) {
	switch ( keysym->sym )
	{
	default:		  
		currMode->handleKeyDown(keysym);
	}
}   	

void LinumesModeManager::updateCurrentMode() {
		ModeManager::release();
		ModeManager::init();
}

void LinumesModeManager::update() {
	// this is the place where we can switch modes based on what has happened from the last update
	if ( currMode->isModeComplete() ){
        if (currMode->getModeName() == SELECTION_MODE ){
            std::pair<std::string, std::map<std::string,std::string> > selection = (dynamic_cast<SelectionMode *>(currMode))->getSelection();
            configureSelectedMode(selection);       
        } else {
            delete currMode;
            currMode = new SelectionMode();
        } 
        updateCurrentMode();
	}
}
