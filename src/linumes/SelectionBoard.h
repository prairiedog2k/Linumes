#ifndef SELECTIONBOARD_H_
#define SELECTIONBOARD_H_

#include "framework/Rendered.h"
#include "SimpleBackground.h"
#include "framework/TextureQuad.h"
#include "framework/Themed.h"
#include "Selection.h"
#include <memory>
#include <string>
#include <list>
#include <map>

class SelectionBoard : public Rendered, public Themed
{	
protected:
	std::string _name;
	TextureQuad _quad;
	auto_ptr<SimpleBackground> _bg;
	std::list< std::pair<std::string, Selection > > _selectionList;
	std::list< std::pair<std::string, Selection > >::iterator _currentSelection;
	//selection name to available options
	std::map< std::string, std::list< Option> > _optionMap;
	std::list<Option> _currentOptions;

public:
	SelectionBoard(std::string name);
	virtual ~SelectionBoard();

	virtual void init(); 
	virtual void Up();
	virtual void Down();
	virtual void update(unsigned int currentTime);
	virtual void Draw();
	virtual bool canExit();
	std::pair<std::string, std::map<std::string, std::string> > getSelectionDisplayAndParameters();

protected:
	virtual std::string getSelectionResource();
	virtual std::string getSelectionsTitle();
	virtual void drawAdditional();
	virtual bool isActiveSelection(std::string strName);
	Selection getSelection();
};

#endif /*SELECTIONBOARD_H_*/
