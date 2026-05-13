#include "framework/MediaManager.h"
#include "SelectionBoard.h"
#include "SelectionTypes.h"
#include "framework/ResourceHelper.h"
#include "framework/Utils.h"


namespace Linumes {
namespace HF = Hunchback::Framework;


SelectionBoard::SelectionBoard(std::string name) : HF::Rendered(true), HF::Themed(), _name(name), _quad(), _bg( std::make_unique<SimpleBackground>(0.0,0.0, BASE_SEL_BG) )
{

}

SelectionBoard::~SelectionBoard()
{
	_selectionList.clear();
}

void SelectionBoard::Up() {
	if (_currentSelection == _selectionList.begin()) {
		_currentSelection = _selectionList.end();
	}
	_currentSelection--;
	_currentOptions = _optionMap[(*_currentSelection).first];
}

void SelectionBoard::Down() {
	_currentSelection++;
	if (_currentSelection == _selectionList.end()) {
		_currentSelection = _selectionList.begin();
	}
	_currentOptions = _optionMap[(*_currentSelection).first];
}

std::pair<std::string, std::map<std::string, std::string> > SelectionBoard::getSelectionDisplayAndParameters() {
	return std::make_pair( (*_currentSelection).first, (*_currentSelection).second.parameters);
}

bool SelectionBoard::isActiveSelection(std::string strName) {
	return ( (*_currentSelection).first == strName);
}

Selection SelectionBoard::getSelection() {
	return (*_currentSelection).second;
}

std::string SelectionBoard::getSelectionResource() {
	return BASE_SELECTIONS;
}

void SelectionBoard::init() {
	if (nullptr != getTheme()) {
		_bg->setTheme(getTheme());
		std::string SettingsConfigFile = HF::ResourceHelper::getStringResource( getTheme(), getSelectionResource())->getResource();
		buildSelectionListFromYaml(SettingsConfigFile, _selectionList, _optionMap);
		_currentSelection = _selectionList.begin();
		_currentOptions = _optionMap[(*_currentSelection).first];
	}
}

void SelectionBoard::update(unsigned int currentTime) {	
	// do nothing
}

void SelectionBoard::drawAdditional() {
	HF::Font *f0 = HF::ResourceHelper::getFontResource(getTheme(), LINUMES_FONT_72)->getResource();
	f0->setRGB(0.0f,0.0f,0.0f);
	f0->drawText(getSelectionsTitle().c_str(), HF::xformX(513), HF::xformY(619), true);
	f0->setRGB(1.0f,1.0f,1.0f);
	f0->drawText(getSelectionsTitle().c_str(), HF::xformX(512), HF::xformY(620), true);


	HF::Font *f1 = HF::ResourceHelper::getFontResource(getTheme(),  BASE_FONT_24 )->getResource();
	int ypos = 500;
	for (std::list< std::pair < std::string, Selection > >::iterator iter = _selectionList.begin();
	iter != _selectionList.end(); iter++) {
		f1->setRGB(0.0f,0.0f,0.0f);
		f1->drawText((*iter).second.display.c_str(), HF::xformX(513), HF::xformY(ypos-1), true);

		if  ( isActiveSelection( (*iter).first ) ) {
			f1->setRGB(1.0f,0.0f,0.0f);
		} else {
			f1->setRGB(1.0f,1.0f,1.0f);
		}
		f1->drawText((*iter).second.display.c_str(), HF::xformX(512), HF::xformY(ypos), true);
		ypos -= 50;
	}
}

bool SelectionBoard::canExit() {
	return getSelection().type == SEL_TYPE_EXIT;
}

std::string SelectionBoard::getSelectionsTitle() {
	return "l  i  n  u  m  e  s";
}

void SelectionBoard::Draw() {
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity( );
	glTranslatef( 0.0f, 0.0f, -10.0f );

	_bg->Draw();

	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glBindTexture( GL_TEXTURE_2D, HF::ResourceHelper::getTextureResource(getTheme(),  SELECTION_TBL_TEXTURE)->getResource());

	glTranslatef( 0.0,0.0, -5.0f );

	_quad.setDimensionAndPosition2D(0.0,0.0,3.0f);
	_quad.setZ(1.0f);
	_quad.Draw();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	drawAdditional();

	/* Draw it to the screen */
	SDL_GL_SwapWindow(HF::MediaManager::getWindow());
}


} // namespace Linumes