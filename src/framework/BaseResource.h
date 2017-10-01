#ifndef BASERESOURCE_
#define BASERESOURCE_

#include <iostream>

using namespace std;

class BaseResource {
public:
	BaseResource() {};
	virtual ~BaseResource() {};
	virtual bool load() = 0;
	virtual bool release() = 0;
	virtual void reportResourceFile() = 0;
};

#endif /*BASERESOURCE_*/
