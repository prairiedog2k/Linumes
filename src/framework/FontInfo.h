#ifndef FONTINFO_H_
#define FONTINFO_H_

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
	int getPointSize() { return pointSize;};
	float getRed() { return fgRed; };
	float getGreen() { return fgGreen; };
	float getBlue() { return fgBlue; };
	void setPointSize(int arg) { pointSize = arg; };
	void setRed(float arg) { fgRed = arg; };
	void setGreen(float arg) { fgGreen = arg; };
	void setBlue(float arg) { fgBlue = arg; }; 
};

#endif /*FONTINFO_H_*/
