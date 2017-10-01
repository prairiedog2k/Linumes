#include "PluginResource.h"
#ifndef MING_NO_PLUGIN
#include <dlfcn.h>
#endif

PluginResource::PluginResource(void *info, string argResourceFile): GenericResource<void *>(argResourceFile)
{
}

PluginResource::~PluginResource()
{
}

bool PluginResource::load() {
#ifndef MING_NO_PLUGIN

    value_ = dlopen(resourceFile.c_str(), RTLD_LAZY);
    if (!value_) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return false;
    }
  // reset errors
  dlerror();
#endif  
	return value_ != NULL;
}

bool PluginResource::release() {
#ifndef MING_NO_PLUGIN
	if (NULL != value_) {
	  dlclose(value_);
	  value_ = NULL;	
	}
	return value_ == NULL;
#endif
}
