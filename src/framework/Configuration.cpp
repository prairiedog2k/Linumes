/*
 * Configuration.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#include "Configuration.h"
#include "ConfigurationTypes.h"
#include "xmlParser.h"
#include "FileUtils.h"
#include <cstdio>

Configuration::Configuration() {

}

Configuration::Configuration(std::string configurationFile) : _configurationFile(configurationFile) {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

void Configuration::init() {
	if (_configurationFile == "") {
		return;
	}
	if (fileExists(_configurationFile)) {
		XMLNode xMainNode = XMLNode::openFileHelper(_configurationFile.c_str(), CFG_ROOT);
		XMLNode configuration;
		int i = 0;
		if (! xMainNode.isEmpty()) {
			do {
				configuration = xMainNode.getChildNode(CFG_CFG, &i);
				if (! configuration.isEmpty()) {
					std::string strName = configuration.getAttribute(CFG_ATTR_NAME) == NULL ? "" : configuration.getAttribute(CFG_ATTR_NAME) ;
					std::string strVal = configuration.getAttribute(CFG_ATTR_VALUE) == NULL ? "" : configuration.getAttribute(CFG_ATTR_VALUE);
					_configurations[strName] = strVal;
				}
			} while (! configuration.isEmpty());
		}
	}
}

bool Configuration::hasKey(std::string key) {
	std::map<std::string, std::string>::iterator iter = _configurations.find(key);
	return iter != _configurations.end();
}

std::string Configuration::getValue(std::string name) {
	return _configurations[name];
}

void Configuration::set(std::string name, std::string value) {
	_configurations[name] = value;
}

void Configuration::release() {
	XMLNode root = XMLNode::createXMLTopNode(CFG_ROOT);
	for (std::map<std::string, std::string>::iterator iter = _configurations.begin(); iter != _configurations.end(); iter++) {
		char buff[64];
		XMLNode cfg = root.addChild(CFG_CFG);
		sprintf(buff,"%s", (*iter).first.c_str());
		cfg.addAttribute(CFG_ATTR_NAME,buff);
		sprintf(buff,"%s", (*iter).second.c_str());
		cfg.addAttribute(CFG_ATTR_VALUE,buff);
	}
	root.writeToFile(_configurationFile.c_str(),"utf-8");
	_configurations.clear();
}
