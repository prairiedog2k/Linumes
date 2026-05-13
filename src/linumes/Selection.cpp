/*
 * Selection.cpp
 */
#include "Selection.h"
#include <yaml-cpp/yaml.h>


namespace Linumes {


void buildSelectionListFromYaml(std::string selectionFile,
        std::list< std::pair<std::string, Selection> > &selectionList,
        std::map< std::string, std::list<Option> > &optionMap) {
    YAML::Node root = YAML::LoadFile(selectionFile);
    if (!root["selections"]) return;

    for (const auto& sel_node : root["selections"]) {
        Selection sel;
        sel.useOption = false;
        sel.display = sel_node["display"] ? sel_node["display"].as<std::string>() : "";
        sel.name    = sel_node["name"]    ? sel_node["name"].as<std::string>()    : "";
        sel.type    = sel_node["type"]    ? sel_node["type"].as<std::string>()    : "";

        std::string id = sel.name.empty() ? sel.display : sel.name;

        if (sel.display.empty()) continue;

        if (sel_node["params"]) {
            for (const auto& kv : sel_node["params"]) {
                sel.parameters[kv.first.as<std::string>()] = kv.second.as<std::string>();
            }
        }

        if (sel_node["options"]) {
            sel.useOption = true;
            std::list<Option> optionList;
            for (const auto& opt_node : sel_node["options"]) {
                Option opt;
                opt.display = opt_node["display"] ? opt_node["display"].as<std::string>() : "";
                opt.value   = opt_node["value"]   ? opt_node["value"].as<std::string>()   : "";
                optionList.push_back(opt);
            }
            optionMap[id] = optionList;
        }

        selectionList.push_back(std::make_pair(id, sel));
    }
}


} // namespace Linumes