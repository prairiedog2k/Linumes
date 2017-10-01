#include "FontInfoBuilder.h"
#include "FontTypes.h"
#include <string>
#include <cstdlib>

FontInfo FontInfoBuilder::createFontInfo(XMLNode fontNode) {
	FontInfo fontInfo;
	if (! fontNode.isEmpty()) {
		std::string strPoint( fontNode.getAttribute(FONT_POINT_SIZE));
		std::string strRed( fontNode.getAttribute(FONT_RED));
		std::string strGreen(fontNode.getAttribute(FONT_GREEN));
		std::string strBlue(fontNode.getAttribute(FONT_BLUE));
		if ( (strPoint.size() > 0) &&
				(strRed.size() > 0) &&
				(strGreen.size() > 0) &&
				(strBlue.size() > 0) ) {
			int pointSize = atoi(strPoint.c_str());
			float red = atof(strRed.c_str());
			float green = atof(strGreen.c_str());
			float blue = atof(strBlue.c_str());
			fontInfo.setPointSize(pointSize);
			fontInfo.setRed(red);
			fontInfo.setGreen(green);
			fontInfo.setBlue(blue);
		}
	}
	return fontInfo;
}

