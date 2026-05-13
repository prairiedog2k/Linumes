#ifndef FONTINFOBUILDER_H_
#define FONTINFOBUILDER_H_

#include "FontInfo.h"
#include <yaml-cpp/yaml.h>

class FontInfoBuilder
{
public:
  static FontInfo createFontInfo(const YAML::Node& fontNode);
};

#endif /*FONTINFOBUILDER_H_*/
