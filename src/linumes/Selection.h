/*
 * Selection.h
 */

#pragma once

#include <string>
#include <map>
#include <list>

namespace Hunchback::Linumes {

typedef struct {
    std::string display;
    std::string value;
} Option;

typedef struct {
    std::string name;
    std::string display;
    std::string type;
    std::map<std::string, std::string> parameters;
    bool useOption;
} Selection;

void buildSelectionListFromYaml(std::string selectionFile,
        std::list< std::pair<std::string, Selection> > &selectionList,
        std::map< std::string, std::list<Option> > &optionMap);

} // namespace Hunchback::Linumes
