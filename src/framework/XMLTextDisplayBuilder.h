#ifndef XMLTEXTDISPLAYBUILDER_H_
#define XMLTEXTDISPLAYBUILDER_H_

#include "BaseTextDisplay.h"
#include "xmlParser.h"

class XMLTextDisplayBuilder
{
private:
	XMLTextDisplayBuilder() {};
	virtual ~XMLTextDisplayBuilder() {};
public:
  static BaseTextDisplay createTextDisplay(XMLNode node);
};

#endif /*XMLTEXTDISPLAYBUILDER_H_*/
