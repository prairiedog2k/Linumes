#ifndef GENERICRESOURCE_H_
#define GENERICRESOURCE_H_

#include <iostream>
#include <string>

#include "BaseResource.h"

using namespace std;

template<class T> 
class GenericResource : public BaseResource {
protected:
	T value_;
	std::string resourceFile;
public:
	GenericResource( std::string argResourceFile) : BaseResource(), resourceFile(argResourceFile) {};
	virtual ~GenericResource() {};
	const T getResource() { return value_;};
	virtual void reportResourceFile() { cout << "resource file : " << resourceFile << endl; }
};

#endif /*GENERICRESOURCE_H_*/
