/*
 * Selection.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#ifndef SELECTION_H_
#define SELECTION_H_

#include <string>
#include <map>
#include <list>

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

void buildSelectionListFromXml(std::string selectionFile,
		std::list< std::pair<std::string, Selection > > &selectionList,
		std::map< std::string, std::list < Option > > &optionMap );

#endif /* SELECTION_H_ */
