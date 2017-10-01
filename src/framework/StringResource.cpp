#include "StringResource.h"

bool StringResource::load() {
	value_ = resourceFile;
	return true;
}

bool StringResource::release(){
	value_ = "";
	return true;
}

