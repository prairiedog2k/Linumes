#ifndef HUD_H_
#define HUD_H_

#include "framework/Themed.h"
#include "framework/Rendered.h"
#include "framework/BaseTextDisplay.h"
#include <string>
#include <map>

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class HUD : public HF::Themed, public HF::Rendered
{
public:
    HUD();
    HUD(bool render);
    virtual ~HUD();
    void setTheme(HF::Theme *theme);
    void setValue(std::string argName, std::string argValue);
    void overrideText(std::string argName, std::string argValue);
    void Draw();
private:
    void loadHudConfig(std::string hudConfigFile);
    std::map<std::string, HF::BaseTextDisplay> textDisplays;
};

} // namespace Hunchback::Linumes

#endif /*HUD_H_*/
