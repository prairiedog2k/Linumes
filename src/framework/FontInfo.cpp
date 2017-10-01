#include "FontInfo.h"

FontInfo::FontInfo() : pointSize(36), fgRed(1.0f), fgGreen(1.0f), fgBlue(1.0f)
{
}

FontInfo::FontInfo(const FontInfo &fi) {
	pointSize = fi.pointSize;
	fgRed = fi.fgRed;
	fgGreen = fi.fgGreen;
	fgBlue = fi.fgBlue;
}

FontInfo::~FontInfo()
{
}
