#include "HUD.h"
#include "HUDTextTypes.h"
#include "framework/TextDisplayTypes.h"
#include "framework/XMLTextDisplayBuilder.h"
#include "framework/ResourceHelper.h"
#include "framework/FontResource.h"
#include "framework/Font.h"
#include "framework/StringResource.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

HUD::HUD() : Rendered(true)
{
    textDisplays.clear();
}

HUD::HUD(bool rendered) : Rendered(rendered)
{
    textDisplays.clear();
}

HUD::~HUD()
{
}

void HUD::loadHudConfig(std::string hudConfigFile) {
    YAML::Node root = YAML::LoadFile(hudConfigFile);
    if (!root["text_displays"]) return;
    textDisplays.clear();
    for (const auto& node : root["text_displays"]) {
        std::string name = node[TEXT_DISPLAY_ATTR_NAME] ? node[TEXT_DISPLAY_ATTR_NAME].as<std::string>() : "";
        if (!name.empty()) {
            BaseTextDisplay btd = XMLTextDisplayBuilder::createTextDisplay(node);
            textDisplays[name] = btd;
        }
    }
}

void HUD::overrideText(std::string argName, std::string argValue) {
    std::map<std::string, BaseTextDisplay>::iterator iter = textDisplays.find(argName);
    if (iter != textDisplays.end()) {
        BaseTextDisplay btd = iter->second;
        btd.setBaseText(argValue);
        textDisplays[argName] = btd;
    }
}

void HUD::setValue(std::string argName, std::string argValue) {
    std::map<std::string, BaseTextDisplay>::iterator iter = textDisplays.find(argName);
    if (iter != textDisplays.end()) {
        BaseTextDisplay btd = iter->second;
        btd.setValue(argValue);
        textDisplays[argName] = btd;
    }
}

void HUD::setTheme(Theme *theme) {
    if (NULL != theme) {
        StringResource *sr = ResourceHelper::getStringResource(theme, HUD_FILE);
        if (NULL != sr) {
            std::string hudConfigFile = sr->getResource();
            if (!hudConfigFile.empty()) {
                loadHudConfig(hudConfigFile);
            }
        }
    }
    Themed::setTheme(theme);
}

void HUD::Draw() {
    if (isRenderable()) {
        FontResource *fr = ResourceHelper::getFontResource(getTheme(), HUD_FONT);
        Font *font = fr->getResource();

        for (std::map<std::string, BaseTextDisplay>::iterator iter = textDisplays.begin();
             iter != textDisplays.end(); iter++) {
            BaseTextDisplay btd = iter->second;
            if (btd.hasDrop()) {
                font->drawText(btd.getFormattedText().c_str(), btd.getX()+1, btd.getY()+1, 1.0f, 1.0f, 1.0f);
            }
            font->drawText(btd.getFormattedText().c_str(), btd.getX(), btd.getY());
        }
    }
}
