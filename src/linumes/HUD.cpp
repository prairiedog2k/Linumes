#include "HUD.h"
#include "HUDTextTypes.h"
#include "framework/TextDisplayTypes.h"
#include "framework/XMLTextDisplayBuilder.h"
#include "framework/ResourceHelper.h"
#include "framework/FontResource.h"
#include "framework/Font.h"
#include "framework/StringResource.h"
#include "xmlParser.h"
#include <iostream>

HUD::HUD(): Rendered(true)
{
	textDisplays.clear();
}

HUD::HUD(bool rendered): Rendered(rendered)
{
	textDisplays.clear();
}


HUD::~HUD()
{	
	
}

void HUD::loadDisplayItems(XMLNode items) {
		if (! items.isEmpty() ) {
			textDisplays.clear();
			XMLNode node;
		 	int i = 0;
		 	do {	 	
		 	  node = items.getChildNode(TEXT_DISPLAY_NODE, &i);
		 	  if (! node.isEmpty()) {		 	  	
		 	  	std::string strName = node.getAttribute(TEXT_DISPLAY_ATTR_NAME);		 	  	
		 	  	BaseTextDisplay btd = XMLTextDisplayBuilder::createTextDisplay(node);
		 	  	textDisplays[strName] = btd;
		 	  }
		 	}  while ( ! node.isEmpty() );
		}
}

void HUD::loadHudConfig(std::string hudConfigFile) {
	XMLNode xMainNode=XMLNode::openFileHelper(hudConfigFile.c_str(),HUD_ROOT);
	if (! xMainNode.isEmpty() ) {
		XMLNode items = xMainNode.getChildNode(TEXT_DISPLAY_ROOT);
		loadDisplayItems(items); 
	}
}

void HUD::overrideText(std::string argName, std::string argValue) {
	std::map<std::string, BaseTextDisplay>::iterator iter = textDisplays.find(argName);
	if (iter != textDisplays.end()) {	  		
		BaseTextDisplay btd = (BaseTextDisplay)( ( (pair<std::string,BaseTextDisplay>)(*iter) ).second); 
		btd.setBaseText(argValue);
		textDisplays[argName] = btd;
	}		
}

void HUD::setValue(std::string argName, std::string argValue) {
	std::map<std::string, BaseTextDisplay>::iterator iter = textDisplays.find(argName);
	if (iter != textDisplays.end()) {	  
		
		BaseTextDisplay btd = (BaseTextDisplay)( ( (pair<std::string,BaseTextDisplay>)(*iter) ).second); 
		btd.setValue(argValue);
		textDisplays[argName] = btd;
	}	
}

void HUD::setTheme(Theme *theme) {
	if (NULL != theme) {
		StringResource *sr = ResourceHelper::getStringResource(theme, HUD_FILE);
		if (NULL != sr) {
			std::string hudConfigFile = sr->getResource();
			if (hudConfigFile.size() > 0) {
				loadHudConfig(hudConfigFile);
			}
		}
	}
	Themed::setTheme(theme);
}

void HUD::Draw() {
	if (isRenderable()) {
		FontResource *fr = ResourceHelper::getFontResource(getTheme(), HUD_FONT );
		Font *font = fr->getResource();
		
		for (std::map<std::string,BaseTextDisplay>::iterator iter = textDisplays.begin(); iter != textDisplays.end(); iter++) {
			pair<std::string,BaseTextDisplay> dp = *(iter);
			BaseTextDisplay btd = dp.second;
			if (btd.hasDrop()) {
				font->drawText( btd.getFormattedText().c_str(),btd.getX()+1, btd.getY()+1, 1.0f, 1.0f, 1.0f);
			}
			font->drawText( btd.getFormattedText().c_str(),btd.getX(), btd.getY());
		}
	}
}
