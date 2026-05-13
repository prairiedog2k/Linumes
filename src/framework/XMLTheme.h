#ifndef XMLTHEME_H_
#define XMLTHEME_H_

#include "Theme.h"
#include "AudioInfo.h"
#include <yaml-cpp/yaml.h>
#include "BaseResource.h"

using namespace std;

class XMLTheme : public Theme
{
public:
    XMLTheme();
    XMLTheme(std::string resourcefile);
    XMLTheme(std::string resourcefile, std::string resourcedir);
    virtual ~XMLTheme() {};

    bool loadResourcesFromNode(const YAML::Node& node);

    virtual bool init();

    virtual void release();

private:
    std::string _resourcedir;
    bool loadResources();
};

#endif /*XMLTHEME_H_*/
