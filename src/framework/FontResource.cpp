#include "FontResource.h"
#include <iostream>

namespace Hunchback::Framework {

FontResource::FontResource(void *info, std::string argResourceFile) : GenericResource<Font *>(argResourceFile){
	FontInfo *fi = (FontInfo *)info;
	fontInfo = new FontInfo(*fi);
}

FontResource::~FontResource()
{
	release();
	delete fontInfo;
	fontInfo = nullptr;
}

bool FontResource::load() {
	bool bRetVal = false;
	if ((resourceFile.size() > 0) && (nullptr != fontInfo)) {
		value_ = new Font(resourceFile.c_str(), fontInfo->getPointSize(), fontInfo->getRed(), fontInfo->getGreen(), fontInfo->getBlue() );
		if ( nullptr != value_) {
			value_->initFont();
#ifdef DEBUG
		std::cout << "Loaded Resource " << resourceFile << std::endl;
#endif
		}
		bRetVal = true;
	}
	return bRetVal;
}

bool FontResource::release() {
	if (value_) {
		delete value_;
		value_ = nullptr;
	}
	return true;
}

} // namespace Hunchback::Framework
