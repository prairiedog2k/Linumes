#pragma once

#include <iostream>

namespace Hunchback::Framework {

class BaseResource {
public:
	BaseResource() {};
	virtual ~BaseResource() {};
	virtual bool load() = 0;
	virtual bool release() = 0;
	virtual void reportResourceFile() = 0;
};

} // namespace Hunchback::Framework
