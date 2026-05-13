#include "HighScoreManager.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "HighScoreTypes.h"
#include "framework/ResourceHelper.h"
#include "framework/FileUtils.h"
#include <yaml-cpp/yaml.h>

HighScoreManager::HighScoreManager() : _baseTheme(nullptr), _highScoreFile("") {
}

HighScoreManager::HighScoreManager(Theme *baseTheme) : _baseTheme(baseTheme), _highScoreFile("") {
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::loadHighScores() {
    if (!fileExists(_highScoreFile)) return;
    YAML::Node root = YAML::LoadFile(_highScoreFile);
    if (!root[HI_GAME_MODE]) return;
    for (const auto& gm : root[HI_GAME_MODE]) {
        if (!gm[HI_ATTR_NAME] || !gm[HI_ATTR_MAX_LISTING]) continue;
        std::string modeName = gm[HI_ATTR_NAME].as<std::string>();
        int maxListing = gm[HI_ATTR_MAX_LISTING].as<int>();
        auto table = std::make_unique<HighScoreTable>(modeName, maxListing);
        table->fillTable(gm);
        _tableMap[modeName] = std::move(table);
    }
}

HighScoreTable *HighScoreManager::createHighScoreTable(std::string tableName) {
    return createHighScoreTable(tableName, 10);
}

HighScoreTable *HighScoreManager::createHighScoreTable(std::string tableName, unsigned int maxListings) {
    auto table = std::make_unique<HighScoreTable>(tableName, maxListings);
    HighScoreTable *raw = table.get();
    _tableMap[tableName] = std::move(table);
    return raw;
}

void HighScoreManager::init() {
    if (_baseTheme) {
        StringResource *sr = ResourceHelper::getStringResource(_baseTheme, BASE_HI_REF);
        if (sr) {
            _highScoreFile = sr->getResource();
            if (!_highScoreFile.empty()) {
                loadHighScores();
            }
        }
    }
}

void HighScoreManager::release() {
    YAML::Node root;
    YAML::Node gameModes;
    for (auto& kv : _tableMap) {
        if (kv.second) {
            kv.second->fillYaml(gameModes);
        }
    }
    root[HI_GAME_MODE] = gameModes;
    std::ofstream fout(_highScoreFile);
    fout << root;
    _tableMap.clear();
}
