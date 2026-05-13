#include "PluginResource.h"
#ifndef MING_NO_PLUGIN
#include <dlfcn.h>
#endif

PluginResource::PluginResource(void *info, string argResourceFile): GenericResource<void *>(argResourceFile)
{
}

PluginResource::~PluginResource()
{
  release();
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
	return value_ != nullptr;
}

bool PluginResource::release() {
#ifndef MING_NO_PLUGIN
	if (value_) {
		dlclose(value_);
		value_ = nullptr;
	}
#endif
	return true;
}
