#pragma once

#include "BaseTextDisplay.h"
#include <yaml-cpp/yaml.h>

namespace Hunchback::Framework {

class TextDisplayBuilder
{
private:
    TextDisplayBuilder() {};
    virtual ~TextDisplayBuilder() {};
public:
  static BaseTextDisplay createTextDisplay(const YAML::Node& node);
};

} // namespace Hunchback::Framework
