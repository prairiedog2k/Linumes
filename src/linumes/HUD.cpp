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


namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


HUD::HUD() : HF::Rendered(true)
{
    textDisplays.clear();
}

HUD::HUD(bool rendered) : HF::Rendered(rendered)
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
            HF::BaseTextDisplay btd = HF::XMLTextDisplayBuilder::createTextDisplay(node);
            textDisplays[name] = btd;
        }
    }
}

void HUD::overrideText(std::string argName, std::string argValue) {
    std::map<std::string, HF::BaseTextDisplay>::iterator iter = textDisplays.find(argName);
    if (iter != textDisplays.end()) {
        HF::BaseTextDisplay btd = iter->second;
        btd.setBaseText(argValue);
        textDisplays[argName] = btd;
    }
}

void HUD::setValue(std::string argName, std::string argValue) {
    std::map<std::string, HF::BaseTextDisplay>::iterator iter = textDisplays.find(argName);
    if (iter != textDisplays.end()) {
        HF::BaseTextDisplay btd = iter->second;
        btd.setValue(argValue);
        textDisplays[argName] = btd;
    }
}

void HUD::setTheme(HF::Theme *theme) {
    if (nullptr != theme) {
        HF::StringResource *sr = HF::ResourceHelper::getStringResource(theme, HUD_FILE);
        if (nullptr != sr) {
            std::string hudConfigFile = sr->getResource();
            if (!hudConfigFile.empty()) {
                loadHudConfig(hudConfigFile);
            }
        }
    }
    HF::Themed::setTheme(theme);
}

void HUD::Draw() {
    if (isRenderable()) {
        HF::FontResource *fr = HF::ResourceHelper::getFontResource(getTheme(), HUD_FONT);
        HF::Font *font = fr->getResource();

        for (auto& kv : textDisplays) {
            HF::BaseTextDisplay btd = kv.second;
            if (btd.hasDrop()) {
                font->drawText(btd.getFormattedText().c_str(), btd.getX()+1, btd.getY()+1, 1.0f, 1.0f, 1.0f);
            }
            font->drawText(btd.getFormattedText().c_str(), btd.getX(), btd.getY());
        }
    }
}


} // namespace Hunchback::Linumes