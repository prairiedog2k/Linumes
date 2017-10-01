#ifndef FONTRESOURCE_H_
#define FONTRESOURCE_H_

#include "GenericResource.h"
#include "Font.h"
#include "FontInfo.h"

class FontResource : public GenericResource<Font *>
{
private:
	 FontInfo *fontInfo;
public:
	FontResource(void *info, string argResourceFile);
	virtual ~FontResource();
	bool load();
	bool release();
	
};

#endif /*FONTRESOURCE_H_*/
