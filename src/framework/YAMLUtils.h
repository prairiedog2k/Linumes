#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include "BaseResource.h"

namespace Hunchback::Framework {

BaseResource *createResourceFromNode(const YAML::Node& node, const std::string& themedir);
std::string nodeAttributeAsString(const YAML::Node& node, const char *key);
bool nodeAttributeAsBool(const YAML::Node& node, const char *key);

} // namespace Hunchback::Framework
