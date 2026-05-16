#include "YAMLUtils.h"

#include "ThemeTypes.h"
#include "AudioResource.h"
#include "MusicResource.h"
#include "TextureResource.h"
#include "StringResource.h"
#include "FontResource.h"
#include "PluginResource.h"
#include "FontInfo.h"
#include "FontInfoBuilder.h"

namespace Hunchback::Framework {

std::string nodeAttributeAsString(const YAML::Node& node, const char *key) {
    if (node[key]) return node[key].as<std::string>();
    return "";
}

bool nodeAttributeAsBool(const YAML::Node& node, const char *key) {
    if (!node[key]) return false;
    return node[key].as<std::string>() == "true";
}

BaseResource *createResourceFromNode(const YAML::Node& node, const std::string& themedir) {
    if (!node) return nullptr;
    std::string strType = nodeAttributeAsString(node, THEME_ATTR_TYPE);
    std::string strAltDir = nodeAttributeAsString(node, THEME_ATTR_ALTDIR);
    std::string file = nodeAttributeAsString(node, "file");
    std::string path = strAltDir.empty() ? (themedir + "/" + file) : (strAltDir + "/" + file);

    if (strType == RESOURCE_AUDIO) {
        AudioResource *ar = new AudioResource(nullptr, path);
        ar->load();
        return ar;
    }
    if (strType == RESOURCE_TEXTURE) {
        TextureResource *tr = new TextureResource(nullptr, path);
        tr->load();
        return tr;
    }
    if (strType == RESOURCE_FONT) {
        FontInfo fi = FontInfoBuilder::createFontInfo(node);
        FontResource *fr = new FontResource(&fi, path);
        fr->load();
        return fr;
    }
    if (strType == RESOURCE_PLUGIN) {
        PluginResource *pr = new PluginResource(nullptr, path);
        pr->load();
        return pr;
    }
    if (strType == RESOURCE_STRING) {
        StringResource *sr = new StringResource(path);
        sr->load();
        return sr;
    }
    return nullptr;
}

} // namespace Hunchback::Framework
