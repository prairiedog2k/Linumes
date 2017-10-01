#ifndef HUD_H_
#define HUD_H_

#include "framework/Themed.h"
#include "framework/Rendered.h"
#include "framework/BaseTextDisplay.h"
#include "xmlParser.h"
#include <string>
#include <map>

class HUD : public Themed, public Rendered
{
public:
	HUD();
	HUD(bool render);
	virtual ~HUD();
	void setTheme(Theme *theme);
	void setValue(std::string argName, std::string argValue);
	void overrideText(std::string argName, std::string argValue); 
	void Draw();
private:
  void loadDisplayItems(XMLNode items); 
	void loadHudConfig(std::string hudConfigFile);
	std::map<std::string, BaseTextDisplay> textDisplays;	
};

#endif /*HUD_H_*/
