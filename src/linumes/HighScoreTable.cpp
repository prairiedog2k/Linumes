#include "HighScoreTable.h"

#include "HighScoreTypes.h"
#include <cstdlib>
#include <cstdio>

HighScoreTable::HighScoreTable() : _maxSize(10), _tableName("default")
{
}

HighScoreTable::HighScoreTable(std::string tableName, int maxSize ): _maxSize(maxSize), _tableName(tableName) {
	
}

HighScoreTable::~HighScoreTable()
{
	
}

void HighScoreTable::fillXml(XMLNode &topNode) {
	char buff[64];
	XMLNode gameMode = topNode.addChild(HI_GAME_MODE);
	gameMode.addAttribute(HI_ATTR_NAME,_tableName.c_str());

	sprintf(buff,"%d", _maxSize);

	gameMode.addAttribute(HI_ATTR_MAX_LISTING, buff);

	for (std::set< std::pair<int, std::string> >::iterator iter = _scoreTable.begin(); iter != _scoreTable.end(); iter++) {
		XMLNode scorelisting = gameMode.addChild(HI_SCORE_LISTING);
		sprintf(buff,"%s", (*iter).second.c_str());
		scorelisting.addAttribute(HI_ATTR_NAME,buff);
		sprintf(buff,"%d", (*iter).first);
		scorelisting.addAttribute(HI_ATTR_SCORE,buff);
	}
}


void HighScoreTable::fillTable( XMLNode node) {
	if ( node.isEmpty() ) {
		return;
	}
	int i = 0;
	XMLNode currNode;
	unsigned int count = 0;
	do {	 	
		currNode = node.getChildNode(HI_SCORE_LISTING, &i);
		if (! currNode.isEmpty()) {
			if (count >= _maxSize) {
				return;
			}
			std::string strName = currNode.getAttribute(HI_ATTR_NAME);
			int val = atoi( currNode.getAttribute(HI_ATTR_SCORE) );
			std::pair<int, std::string> currPair = std::make_pair(val, strName);
			_scoreTable.insert( currPair );
			count++;
		}
	}  while ( ! currNode.isEmpty() );
}

bool HighScoreTable::addScore(int score, std::string name) {
	bool bRetVal = false;
	std::pair<int, std::string> currPair = std::make_pair(score, name);
	if (_scoreTable.insert(currPair).second ) {
		
		if (_scoreTable.size() > _maxSize ) {
			std::set< std::pair<int, std::string> >::iterator iter = _scoreTable.end();
			iter--;
			_scoreTable.erase( iter );
		}
		bRetVal = true;
	}
	return bRetVal;
}

int HighScoreTable::getHighestScore() {
	//std::set< std::pair<int, std::string> >::iterator iter = _scoreTable.begin();
	return (*( _scoreTable.begin() ) ).first;
}

std::string HighScoreTable::getTableString() {
	std::string retVal;
	char buff[32];
	int count = 1;
	retVal  = "\nRank      Score \n";
	for (std::set< std::pair<int, std::string> >::iterator iter = _scoreTable.begin(); iter != _scoreTable.end(); iter++) {
		sprintf ( buff, "%2d     %7d\n", count, (*iter).first);
		retVal += buff;
		count++;
	}
	return retVal;
}
