#pragma once

#include "GenericResource.h"
#include "Font.h"
#include "FontInfo.h"

namespace Hunchback::Framework {

class FontResource : public GenericResource<Font *>
{
private:
	 FontInfo *fontInfo;
public:
	FontResource(void *info, std::string argResourceFile);
	virtual ~FontResource();
	bool load();
	bool release();

};

} // namespace Hunchback::Framework
