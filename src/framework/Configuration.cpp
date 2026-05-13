/*
 * Configuration.cpp
 */

#include "Configuration.h"
#include "FileUtils.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

Configuration::Configuration() {
}

Configuration::Configuration(std::string configurationFile)
    : _configurationFile(configurationFile) {
}

Configuration::~Configuration() {
}

void Configuration::init() {
    if (_configurationFile.empty()) return;
    if (!fileExists(_configurationFile)) return;

    YAML::Node root = YAML::LoadFile(_configurationFile);
    if (root["configurations"] && root["configurations"].IsMap()) {
        for (const auto& kv : root["configurations"]) {
            _configurations[kv.first.as<std::string>()] = kv.second.as<std::string>();
        }
    }
}

bool Configuration::hasKey(std::string key) {
    return _configurations.find(key) != _configurations.end();
}

std::string Configuration::getValue(std::string name) {
    return _configurations[name];
}

void Configuration::set(std::string name, std::string value) {
    _configurations[name] = value;
}

void Configuration::release() {
    YAML::Node root;
    YAML::Node configs;
    for (const auto& kv : _configurations) {
        configs[kv.first] = kv.second;
    }
    root["configurations"] = configs;
    std::ofstream fout(_configurationFile);
    fout << root;
    _configurations.clear();
}
