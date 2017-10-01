#ifndef FONTINFOBUILDER_H_
#define FONTINFOBUILDER_H_

#include "FontInfo.h"
#include "xmlParser.h"

class FontInfoBuilder
{
public:
  static FontInfo createFontInfo(XMLNode fontNode);
};

#endif /*FONTINFOBUILDER_H_*/

