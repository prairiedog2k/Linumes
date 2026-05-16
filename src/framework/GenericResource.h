#pragma once

#include <iostream>
#include <string>

#include "BaseResource.h"

namespace Hunchback::Framework {

template<class T>
class GenericResource : public BaseResource {
protected:
	T value_;
	std::string resourceFile;
public:
	GenericResource( std::string argResourceFile) : BaseResource(), resourceFile(argResourceFile) {};
	virtual ~GenericResource() {};
	const T getResource() const { return value_;};
	virtual void reportResourceFile() { std::cout << "resource file : " << resourceFile << std::endl; }
};

} // namespace Hunchback::Framework
