#pragma once

#include "GenericResource.h"
#include <string>

namespace Hunchback::Framework {

class StringResource : public  GenericResource<std::string>
{
public:
	StringResource(std::string argResource) : GenericResource<std::string>(argResource){};
	virtual ~StringResource() {};
	bool load();
	bool release();
};

} // namespace Hunchback::Framework
