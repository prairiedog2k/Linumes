#pragma once

#include <string>
#include <sstream>

namespace Hunchback::Framework {

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
	int getX() const;
	int getY() const;
	std::string getType()     const { return type; };
	std::string getValue()    const { return value; };
	std::string getBaseText() const { return baseText; };
	bool hasDrop()            const { return _hasDrop; };
	void setX(int argx) { x = argx;};
	void setY(int argy) { y = argy;};
	void setValue(std::string argValue) { value = argValue; };
	void setType( std::string argType) { type = argType; };
	void setDrop(bool drop) { _hasDrop = drop; };
	void setRelative(bool rel) { _isRelative = rel;};
	std::string getFormattedText() const;
	void setBaseText(std::string argBaseText) { baseText = argBaseText; };
};

} // namespace Hunchback::Framework
