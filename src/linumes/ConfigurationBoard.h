/*
 * LinumesConfigurationBoard.h
 *
 *  Created on: Apr 7, 2011
 *      Author: rigriff
 */

#ifndef LINUMESCONFIGURATIONBOARD_H_
#define LINUMESCONFIGURATIONBOARD_H_

#include "framework/Rendered.h"
#include "SimpleBackground.h"
#include "framework/TextureQuad.h"
#include "framework/Themed.h"
#include "framework/Configuration.h"
#include "Selection.h"
#include "SelectionBoard.h"
#include <memory>
#include <string>
#include <list>
#include <map>

class ConfigurationBoard: public SelectionBoard {
private:
	bool _optionMode;
protected:
	Configuration *_configuration;
	std::list<Option>::iterator _currentOption;
public:
	ConfigurationBoard(std::string name, Configuration *configuration);
	virtual ~ConfigurationBoard();

	virtual void init();
	virtual void Up();
	virtual void Down();
	virtual void Left();
	virtual void Right();
	virtual void Select();
	virtual void update(unsigned int currentTime);

private:
	void alignSelectionsWithConfiguration();
	void updateOptions();
	void drawOptions();
	bool isOptionMode();
	void setOptionMode(bool mode);
	bool isCurrentOptionValue( std::string value );

protected:
	virtual std::string getSelectionsTitle();
	virtual std::string getSelectionResource();
	virtual void drawAdditional();
	Option getOption();
};

#endif /* LINUMESCONFIGURATIONBOARD_H_ */
