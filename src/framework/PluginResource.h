#pragma once

#include "GenericResource.h"
#include <string>

namespace Hunchback::Framework {

class PluginResource: public GenericResource<void *> {
public:
	PluginResource(void *info, std::string argResourceFile);
	virtual ~PluginResource();
	bool load();
	bool release();
};

} // namespace Hunchback::Framework
