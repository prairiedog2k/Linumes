/*
 * Configuration.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <map>


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

#endif /* CONFIGURATION_H_ */
