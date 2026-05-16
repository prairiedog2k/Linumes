#pragma once

#include "FontInfo.h"
#include <yaml-cpp/yaml.h>

namespace Hunchback::Framework {

class FontInfoBuilder
{
public:
  static FontInfo createFontInfo(const YAML::Node& fontNode);
};

} // namespace Hunchback::Framework
