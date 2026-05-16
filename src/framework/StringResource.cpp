#include "StringResource.h"

namespace Hunchback::Framework {

bool StringResource::load() {
	value_ = resourceFile;
	return true;
}

bool StringResource::release(){
	value_ = "";
	return true;
}

} // namespace Hunchback::Framework
