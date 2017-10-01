/*
 * Selection.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */
#include "Selection.h"
#include "SelectionTypes.h"
#include "framework/XMLUtils.h"

void buildSelectionListFromXml(std::string selectionFile,
		std::list< std::pair<std::string, Selection > > &selectionList,
		std::map< std::string, std::list < Option > > &optionMap) {
	XMLNode xMainNode=XMLNode::openFileHelper(selectionFile.c_str(),SEL_ROOT);
	if (! xMainNode.isEmpty() ) {
		XMLNode selection;
		int i = 0;

		do {
			selection = xMainNode.getChildNode(SEL_SELECTION, &i);
			if (! selection.isEmpty()) {
				Selection sel;
				sel.useOption = false;
				sel.display = nodeAttributeAsString(selection, SEL_ATTR_DISPLAY);
				sel.name = nodeAttributeAsString(selection, SEL_ATTR_NAME);
				sel.type = nodeAttributeAsString(selection, SEL_ATTR_TYPE);
				//jackenstein
				std::string id = sel.name == "" ? sel.display : sel.name;
				if (sel.display != "") {
					XMLNode param;
					int j = 0;
					do {
						param = selection.getChildNode(SEL_PARAM, &j);

						if (! param.isEmpty()) {
							std::string strName = nodeAttributeAsString(param, SEL_ATTR_NAME);
							std::string strVal = nodeAttributeAsString(param, SEL_ATTR_VALUE);
							if ((strName != "")&&(strVal != "")) {
								sel.parameters[strName] = strVal;
							}
						}
					} while (! param.isEmpty());

					XMLNode options;
					int nOptions = 0;
					options = selection.getChildNode(SEL_OPTIONS, &nOptions);
					if (! options.isEmpty() ) {

						sel.useOption = true;
						XMLNode option;
						int nOption=0;
						list<Option> optionList;
						do {
							option = options.getChildNode(SEL_OPTION, &nOption);
							if (!option.isEmpty()) {
								Option opt;
								opt.display = nodeAttributeAsString(option, SEL_ATTR_DISPLAY);
								opt.value = nodeAttributeAsString(option, SEL_ATTR_VALUE);
								optionList.push_back( opt );
							}
						} while (!option.isEmpty());

						optionMap[id] = optionList;

					} else {
						//no options
					}
					selectionList.push_back(std::make_pair( id, sel ) );

				}
			}
		} while ( !selection.isEmpty());
	}
}
