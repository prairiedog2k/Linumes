#include "PluggableBackground.h"

#include "framework/ResourceHelper.h"
#ifdef MING_NO_PLUGIN
    //do nothing
#else
    #include "dlfcn.h"
#endif

#include "BoardTypes.h"

PluggableBackground::PluggableBackground() :  _background(nullptr), _theme(nullptr), hasTemplate(false)
{
}

PluggableBackground::~PluggableBackground()
{
}

void PluggableBackground::setTheme(Theme *theme) {
	if (nullptr != theme) {
		_theme = theme;
		PluginResource *pr = ResourceHelper::getPluginResource(theme, std::string(BOARD_BG_PLUGIN));
		if (pr != nullptr) {
			hasTemplate = true;
		}
	}
}

void PluggableBackground::init() {
#ifdef MING_NO_PLUGIN
#else
	if ((nullptr != _theme) && (hasTemplate)) {
		PluginResource *pr = ResourceHelper::getPluginResource(_theme, std::string(BOARD_BG_PLUGIN));
		void *resource = pr->getResource();
		if (nullptr != resource) {
			
	    create_t* create_bg = (create_t*) dlsym(resource, "create");
	    
	    _background = create_bg();
	    
	    if(nullptr != _background) {
	    	_background->setTheme(_theme);
	    	_background->init();
	    }	    
		}
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
#ifdef DEBUG    	
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
#endif        
    }
	}
#endif
}

void PluggableBackground::release() {
#ifdef MING_NO_PLUGIN
#else    
	if ((nullptr != _theme) && (hasTemplate) && (nullptr != _background)) {
		
		_background->release();
		
		PluginResource *pr = ResourceHelper::getPluginResource(_theme, std::string(BOARD_BG_PLUGIN));
		void *resource = pr->getResource();
		
		if (nullptr != resource) {
	    destroy_t* destroy_bg = (destroy_t*) dlsym(resource, "destroy");
	    destroy_bg(_background);
		}
	  const char* dlsym_error = dlerror();
	  if (dlsym_error) {
#ifdef DEBUG    	
       cerr << "Cannot load symbol create: " << dlsym_error << '\n';
#endif      
    }
	}
#endif
}

void PluggableBackground::Draw() {
	if (nullptr != _background) {
		_background->Draw();
	}
}

bool PluggableBackground::hasAnimation() {
	if (nullptr != _background) {
		return _background->hasAnimation();
	}
	return false;
}

bool PluggableBackground::isAnimating() {
	if (nullptr != _background) {
		return _background->isAnimating();
	}
	return false;	
}

void PluggableBackground::startAnimation() {
	if (nullptr != _background) {
		_background->startAnimation();
	}	
}

void PluggableBackground::stopAnimation() {
	if (nullptr != _background) {
		_background->stopAnimation();
	}	
}

void PluggableBackground::update() {
	if (nullptr != _background) {
		_background->update();
	}	
}
