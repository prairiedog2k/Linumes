#ifndef FONTINFO_H_
#define FONTINFO_H_

namespace Hunchback::Framework {

class FontInfo
{
private:
	int pointSize;
  float fgRed;
  float fgGreen;
  float fgBlue;
public:
	FontInfo();
	FontInfo( const FontInfo &fi);
	virtual ~FontInfo();
	int getPointSize() const { return pointSize;};
	float getRed()     const { return fgRed; };
	float getGreen()   const { return fgGreen; };
	float getBlue()    const { return fgBlue; };
	void setPointSize(int arg) { pointSize = arg; };
	void setRed(float arg) { fgRed = arg; };
	void setGreen(float arg) { fgGreen = arg; };
	void setBlue(float arg) { fgBlue = arg; };
};

} // namespace Hunchback::Framework

#endif /*FONTINFO_H_*/
