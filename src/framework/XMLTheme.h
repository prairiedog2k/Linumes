#ifndef XMLTHEME_H_
#define XMLTHEME_H_

#include "Theme.h"
#include "AudioInfo.h"
#include "xmlParser.h"
#include "BaseResource.h"

using namespace std;

class XMLTheme : public Theme
{
public:
    XMLTheme();
	XMLTheme(std::string resourcefile);
	XMLTheme(std::string resourcefile, std::string resourcedir);
	virtual ~XMLTheme() {};

	bool loadResourcesFromNode (XMLNode XMainNode);
	
    virtual bool init();
	
    virtual void release();

private:
	std::string _resourcedir;	
    AudioInfo *getAudioInfo(XMLNode xNode);
	bool loadResources();
};

#endif /*XMLTHEME_H_*/
