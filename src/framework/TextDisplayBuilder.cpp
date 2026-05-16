#include "TextDisplayBuilder.h"
#include "TextDisplayTypes.h"
#include <string>
#include <cstdlib>

namespace Hunchback::Framework {

BaseTextDisplay TextDisplayBuilder::createTextDisplay(const YAML::Node& node) {
    BaseTextDisplay baseTextDisplay;
    if (node) {
        std::string strType = node[TEXT_DISPLAY_ATTR_TYPE] ? node[TEXT_DISPLAY_ATTR_TYPE].as<std::string>() : "";
        std::string strX    = node[TEXT_DISPLAY_ATTR_X]    ? node[TEXT_DISPLAY_ATTR_X].as<std::string>()    : "";
        std::string strY    = node[TEXT_DISPLAY_ATTR_Y]    ? node[TEXT_DISPLAY_ATTR_Y].as<std::string>()    : "";
        bool hasDrop    = node[TEXT_DISPLAY_ATTR_DROP] ? node[TEXT_DISPLAY_ATTR_DROP].as<std::string>() == "true" : false;
        bool isRelative = node[TEXT_DISPLAY_ATTR_REL]  ? node[TEXT_DISPLAY_ATTR_REL].as<std::string>()  == "true" : false;
        std::string baseText = node["text"] ? node["text"].as<std::string>() : "\n";

        if (!strType.empty() && !strX.empty() && !strY.empty()) {
            baseTextDisplay.setBaseText(baseText);
            baseTextDisplay.setType(strType);
            baseTextDisplay.setX(std::stoi(strX));
            baseTextDisplay.setY(std::stoi(strY));
            baseTextDisplay.setDrop(hasDrop);
            baseTextDisplay.setRelative(isRelative);
            baseTextDisplay.setValue("");
        }
    }
    return baseTextDisplay;
}

} // namespace Hunchback::Framework
