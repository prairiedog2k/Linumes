#ifndef BASETEXTDISPLAY_H_
#define BASETEXTDISPLAY_H_

#include <string>
#include <sstream>

class BaseTextDisplay
{
protected:
	int x; 
	int y;	
	std::string baseText;
	std::string value;
	std::string type;
	bool _hasDrop;
	bool _isRelative;
public:
	BaseTextDisplay();
	virtual ~BaseTextDisplay();
	int getX();
	int getY();
	std::string getType() { return type; };
	std::string getValue() { return value; };
	std::string getBaseText() { return baseText; };
	bool hasDrop() { return _hasDrop; };
	void setX(int argx) { x = argx;};
	void setY(int argy) { y = argy;};
	void setValue(std::string argValue) { value = argValue; };
	void setType( std::string argType) { type = argType; };
	void setDrop(bool drop) { _hasDrop = drop; };
	void setRelative(bool rel) { _isRelative = rel;};
	std::string getFormattedText();
	void setBaseText(std::string argBaseText) { baseText = argBaseText; };
};

#endif /*BASETEXTDISPLAY_H_*/
