#include "FontInfoBuilder.h"
#include "FontTypes.h"
#include <string>
#include <cstdlib>

FontInfo FontInfoBuilder::createFontInfo(const YAML::Node& fontNode) {
    FontInfo fontInfo;
    if (fontNode) {
        if (!fontNode[FONT_POINT_SIZE] || !fontNode[FONT_RED] ||
            !fontNode[FONT_GREEN]      || !fontNode[FONT_BLUE]) {
            return fontInfo;
        }
        int pointSize = fontNode[FONT_POINT_SIZE].as<int>(0);
        float red   = fontNode[FONT_RED].as<float>(0.0f);
        float green = fontNode[FONT_GREEN].as<float>(0.0f);
        float blue  = fontNode[FONT_BLUE].as<float>(0.0f);
        if (pointSize > 0) {
            fontInfo.setPointSize(pointSize);
            fontInfo.setRed(red);
            fontInfo.setGreen(green);
            fontInfo.setBlue(blue);
        }
    }
    return fontInfo;
}
