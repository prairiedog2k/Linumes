#ifndef PLUGINRESOURCE_H_
#define PLUGINRESOURCE_H_

#include "GenericResource.h"
#include <string>

using namespace std;

class PluginResource: public GenericResource<void *> {
public:
	PluginResource(void *info, string argResourceFile);
	virtual ~PluginResource();
	bool load();
	bool release();
};

#endif /*PLUGINRESOURCE_H_*/
