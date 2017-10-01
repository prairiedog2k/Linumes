#include "HighScoreManager.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "HighScoreTypes.h"
#include "framework/ResourceHelper.h"
#include "framework/FileUtils.h"

HighScoreManager::HighScoreManager() : _baseTheme(NULL), _highScoreFile("") {

}

HighScoreManager::HighScoreManager(Theme *baseTheme) : _baseTheme(baseTheme) , _highScoreFile(""){

}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::loadHighScores() {
	if (fileExists(_highScoreFile)) {
		XMLNode xMainNode=XMLNode::openFileHelper(_highScoreFile.c_str(),HI_ROOT);
		if (! xMainNode.isEmpty() ) {
			int pos = 0;
			XMLNode gameMode;
			do { 
				gameMode = xMainNode.getChildNode(HI_GAME_MODE, &pos);
				if ( (!gameMode.isEmpty() ) && 
				     ( ( NULL != gameMode.getAttribute(HI_ATTR_NAME) ) && 
					   ( NULL != gameMode.getAttribute(HI_ATTR_MAX_LISTING) ) ) ) {
					std::string modeName =  gameMode.getAttribute(HI_ATTR_NAME);
					int maxListing = atoi( gameMode.getAttribute(HI_ATTR_MAX_LISTING) );
					HighScoreTable *table = new HighScoreTable(modeName, maxListing);
					table->fillTable( gameMode );
					_tableMap[modeName] = table;
				}
			} while ( !gameMode.isEmpty());
		}
	} 
}

HighScoreTable *HighScoreManager::createHighScoreTable(std::string tableName) {
	return createHighScoreTable(tableName, 10);

}
HighScoreTable *HighScoreManager::createHighScoreTable(std::string tableName, unsigned int maxListings) {
	return _tableMap[tableName] = new HighScoreTable(tableName, maxListings); 
}

void HighScoreManager::init() {
	if (NULL != _baseTheme) {
		StringResource *sr = ResourceHelper::getStringResource(_baseTheme, BASE_HI_REF);
		if (NULL != sr) {
			_highScoreFile = sr->getResource();
			if (_highScoreFile.size() > 0) {
				loadHighScores();
			}
		} else {
		}
	}
}

void HighScoreManager::release() {
	XMLNode top = XMLNode::createXMLTopNode(HI_ROOT);
	for (std::map<std::string, HighScoreTable*>::iterator iter = _tableMap.begin(); iter != _tableMap.end(); iter++) {
		HighScoreTable *ptr = (*iter).second;
		if (NULL != ptr) {
			ptr->fillXml( top );
		}
		delete ptr;
	}
	top.writeToFile(_highScoreFile.c_str(),"utf-8");
	_tableMap.clear();
}
