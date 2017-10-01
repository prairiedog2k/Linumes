#ifndef XML_UTILS_H
#define XML_UTILS_H

#include <string>
#include "xmlParser.h"
#include "BaseResource.h"

BaseResource *createResourceFromNode(XMLNode node, std::string themedir);
std::string nodeAttributeAsString(XMLNode node, const char *attributeName);
bool nodeAttributeAsBool(XMLNode node, const char *attributeName);
bool nodeHasAttribute(XMLNode node, const char * attr);

#endif
