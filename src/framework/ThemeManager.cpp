/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "ThemeManager.h"
#include "XMLThemeManagerTypes.h"
#include "XMLThemeTypes.h"
#include "Theme.h"
#include "XMLTheme.h"
#include <yaml-cpp/yaml.h>
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

namespace Hunchback::Framework {

ThemeManager::ThemeManager() : themesFile(DEFAULT_FILE) {
}

ThemeManager::ThemeManager(std::string filename) : themesFile(filename) {
}

ThemeManager::~ThemeManager() = default;

bool ThemeManager::initXML() {
    bool bRetVal = false;
    if (!_currentTheme) {
        YAML::Node root = YAML::LoadFile(themesFile);
        if (!root) return false;

        if (root["base_theme"]) {
            const YAML::Node& bt = root["base_theme"];
            auto bt_theme = std::make_unique<XMLTheme>();
            bt_theme->loadResourcesFromNode(bt);
            _baseTheme = std::move(bt_theme);
        }

        if (root["themes"]) {
            for (const auto& ti : root["themes"]) {
                std::string name = ti["name"] ? ti["name"].as<std::string>() : "";
                std::string file = ti["file"] ? ti["file"].as<std::string>() : "";
                std::string dir  = ti["dir"]  ? ti["dir"].as<std::string>()  : "";
                nameList.push_back(std::make_pair(name, file));
                themeList.push_back(std::make_pair(file, dir));
            }
        }
        themeIterator = themeList.begin();
        bRetVal = !themeList.empty();
        getNextTheme(); // sets _currentTheme internally
    }
    return bRetVal;
}

bool ThemeManager::initData() {
    return false;
}

bool ThemeManager::init() {
    return initXML();
}

Theme *ThemeManager::getNamedTheme(std::string themeName) {
    if (themeName.empty()) return nullptr;

    std::string fileName;
    for (auto& kv : nameList) {
        if (kv.first == themeName) {
            fileName = kv.second;
            break;
        }
    }
    if (fileName.empty()) return nullptr;

    for (auto& kv : themeList) {
        if (kv.first == fileName) {
            if (kv.second.empty()) {
                _currentTheme = std::make_unique<XMLTheme>(kv.first);
            } else {
                _currentTheme = std::make_unique<XMLTheme>(kv.first, kv.second);
            }
            _currentTheme->setBaseTheme(_baseTheme.get());
            _currentTheme->init();
            return _currentTheme.get();
        }
    }
    return nullptr;
}

Theme *ThemeManager::getNextTheme() {
    std::pair<std::string, std::string> filedirpair = *themeIterator;

    if (filedirpair.second.empty()) {
        _currentTheme = std::make_unique<XMLTheme>(filedirpair.first);
    } else {
        _currentTheme = std::make_unique<XMLTheme>(filedirpair.first, filedirpair.second);
    }
    if (++themeIterator == themeList.end()) {
        themeIterator = themeList.begin();
    }
    _currentTheme->setBaseTheme(_baseTheme.get());
    _currentTheme->init();
    return _currentTheme.get();
}

} // namespace Hunchback::Framework
