/*
 * Configuration.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#pragma once

#include <string>
#include <map>

namespace Hunchback::Framework {

class Configuration {
private:
	std::string _configurationFile;
	std::map< std::string, std::string> _configurations;

public:
	Configuration();
	Configuration(std::string config);
	virtual ~Configuration();
	void init();
	bool hasKey(std::string key);
	std::string getValue(std::string name);
	void set(std::string name, std::string value);
	void release();
};

} // namespace Hunchback::Framework
