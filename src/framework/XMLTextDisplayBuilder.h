#ifndef XMLTEXTDISPLAYBUILDER_H_
#define XMLTEXTDISPLAYBUILDER_H_

#include "BaseTextDisplay.h"
#include <yaml-cpp/yaml.h>

class XMLTextDisplayBuilder
{
private:
    XMLTextDisplayBuilder() {};
    virtual ~XMLTextDisplayBuilder() {};
public:
  static BaseTextDisplay createTextDisplay(const YAML::Node& node);
};

#endif /*XMLTEXTDISPLAYBUILDER_H_*/
