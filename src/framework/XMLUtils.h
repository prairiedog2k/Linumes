#ifndef XML_UTILS_H
#define XML_UTILS_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "BaseResource.h"

BaseResource *createResourceFromNode(const YAML::Node& node, const std::string& themedir);
std::string nodeAttributeAsString(const YAML::Node& node, const char *key);
bool nodeAttributeAsBool(const YAML::Node& node, const char *key);

#endif
