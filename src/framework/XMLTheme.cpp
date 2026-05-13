#include "XMLTheme.h"
#include "XMLThemeTypes.h"
#include "AudioResource.h"
#include "MusicResource.h"
#include "TextureResource.h"
#include "StringResource.h"
#include "FontResource.h"
#include "PluginResource.h"
#include "FontInfo.h"
#include "FontInfoBuilder.h"
#include "XMLSongBuilder.h"
#include "XMLSongTypes.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include "SDL.h"
#include "XMLUtils.h"

namespace Hunchback::Framework {

XMLTheme::XMLTheme() : Theme(std::string("")), _resourcedir(std::string("")) {
}

XMLTheme::XMLTheme(std::string resourcefile) : Theme(resourcefile) {
}

XMLTheme::XMLTheme(std::string resourcefile, std::string resourcedir)
    : Theme(resourcefile), _resourcedir(resourcedir) {
}

bool XMLTheme::loadResourcesFromNode(const YAML::Node& xMainNode) {
    if (!xMainNode) return false;

    if (xMainNode["dir"]) {
        themedir = xMainNode["dir"].as<std::string>();
    }
    if (_resourcedir != "") {
        themedir = _resourcedir + "/" + themedir;
    }

    // music resource
    MusicResource *mr = XMLSongBuilder::createMusicResource(xMainNode, themedir);
    if (mr != nullptr) {
        std::string songName = "audio_song";
        if (xMainNode["song"] && xMainNode["song"]["name"]) {
            songName = xMainNode["song"]["name"].as<std::string>();
        }
        resources[songName] = mr;
        resourceCount++;
    }

    // other resources
    if (xMainNode["resources"]) {
        for (const auto& res : xMainNode["resources"]) {
            std::string strType = nodeAttributeAsString(res, THEME_ATTR_TYPE);
            std::string strName = nodeAttributeAsString(res, THEME_ATTR_NAME);
            std::string strAltDir = nodeAttributeAsString(res, THEME_ATTR_ALTDIR);
            std::string file = nodeAttributeAsString(res, "file");
            std::string path = strAltDir.empty() ? (themedir + "/" + file) : (strAltDir + "/" + file);

            if (strType == RESOURCE_AUDIO) {
                resourceCount++;
                AudioResource *ar = new AudioResource(nullptr, path);
                ar->load();
                resources[strName] = ar;
            } else if (strType == RESOURCE_TEXTURE) {
                resourceCount++;
                TextureResource *tr = new TextureResource(nullptr, path);
                tr->load();
                resources[strName] = tr;
            } else if (strType == RESOURCE_FONT) {
                resourceCount++;
                FontInfo fi = FontInfoBuilder::createFontInfo(res);
                FontResource *fr = new FontResource(&fi, path);
                fr->load();
                resources[strName] = fr;
            } else if (strType == RESOURCE_PLUGIN) {
                resourceCount++;
                PluginResource *pr = new PluginResource(nullptr, path);
                pr->load();
                resources[strName] = pr;
            } else if (strType == RESOURCE_STRING) {
                resourceCount++;
                StringResource *sr = new StringResource(path);
                sr->load();
                resources[strName] = sr;
            }
        }
    }
    return true;
}

bool XMLTheme::loadResources() {
    std::string path = themefile;
    if (_resourcedir != "") {
        path = _resourcedir + "/" + themefile;
    }
    YAML::Node root = YAML::LoadFile(path);
    return loadResourcesFromNode(root);
}

bool XMLTheme::init() {
    return loadResources();
}

void XMLTheme::release() {
    Theme::release();
}

} // namespace Hunchback::Framework
