#ifndef STRINGRESOURCE_H_
#define STRINGRESOURCE_H_

#include "GenericResource.h"
#include <string>

class StringResource : public  GenericResource<std::string>
{
public:
	StringResource(std::string argResource) : GenericResource<std::string>(argResource){};
	virtual ~StringResource() {};	
	bool load();
	bool release();
};

#endif /*STRINGRESOURCE_H_*/
