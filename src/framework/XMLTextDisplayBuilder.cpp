#include "XMLTextDisplayBuilder.h"
#include "TextDisplayTypes.h"
#include <string>
#include <cstdlib>

BaseTextDisplay XMLTextDisplayBuilder::createTextDisplay(XMLNode node) {
	BaseTextDisplay baseTextDisplay;
	if (! node.isEmpty()) {				
		std::string strType( node.getAttribute(TEXT_DISPLAY_ATTR_TYPE));
		std::string strX( node.getAttribute(TEXT_DISPLAY_ATTR_X));
		std::string strY( node.getAttribute(TEXT_DISPLAY_ATTR_Y));
		std::string hasDrop( NULL == node.getAttribute(TEXT_DISPLAY_ATTR_DROP) ? "false" : node.getAttribute(TEXT_DISPLAY_ATTR_DROP));
		std::string isRelative ( NULL == node.getAttribute(TEXT_DISPLAY_ATTR_REL) ? "false" : node.getAttribute(TEXT_DISPLAY_ATTR_REL));
		
		std::string baseText( NULL != node.getText() ? node.getText() : "\n"); 	  
		if ( (strType.size() > 0) && 
				(strX.size() > 0) && 
				(strY.size() > 0) && 
				(baseText.size() > 0 ) ){
			baseTextDisplay.setBaseText(baseText);
			baseTextDisplay.setType(strType);
			baseTextDisplay.setX(atoi(strX.c_str()));
			baseTextDisplay.setY(atoi(strY.c_str()));
			baseTextDisplay.setDrop( hasDrop.compare("true") == 0);
			baseTextDisplay.setRelative(isRelative.compare("true") == 0 );
			baseTextDisplay.setValue( "" );
		}
	}	
	return baseTextDisplay;	
}

