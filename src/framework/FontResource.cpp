#include "FontResource.h"
#include <iostream>

FontResource::FontResource(void *info, string argResourceFile) : GenericResource<Font *>(argResourceFile){
	FontInfo *fi = (FontInfo *)info;
	fontInfo = new FontInfo(*fi);	
}

FontResource::~FontResource()
{
	if (fontInfo) {
		delete fontInfo;
	}
}

bool FontResource::load() {
	bool bRetVal = false;
	if ((resourceFile.size() > 0) && (NULL != fontInfo)) {
		value_ = new Font(resourceFile.c_str(), fontInfo->getPointSize(), fontInfo->getRed(), fontInfo->getGreen(), fontInfo->getBlue() );
		if ( NULL != value_) {
			value_->initFont();
#ifdef DEBUG
		std::cout << "Loaded Resource " << resourceFile << endl;
#endif			
		}
		bRetVal = true;
	}
	return bRetVal;
}

bool FontResource::release() {
	if (NULL != value_) {
		delete value_;
	}
	return (NULL == value_);
}
