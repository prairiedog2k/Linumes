#ifndef HIGHSCORETABLE_H_
#define HIGHSCORETABLE_H_

#include <string>
#include <set>
#include "xmlParser.h"

struct hscomp{
	bool operator()(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs) const{
		return lhs.first > rhs.first;
	};
};

typedef std::set< std::pair<int, std::string>, hscomp > ScoreTable;

class HighScoreTable
{
private:
	unsigned int _maxSize;
	std::string _tableName;
	ScoreTable _scoreTable;
	
public:
	HighScoreTable();
	HighScoreTable(std::string tableName, int maxSize );
	virtual ~HighScoreTable();
	void fillXml(XMLNode &topNode);
	void fillTable( XMLNode node);
	bool addScore(int score, std::string name = " ");
	int getHighestScore();
	std::string getTableString();	
};

#endif /*HIGHSCORETABLE_H_*/
