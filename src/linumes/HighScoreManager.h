#ifndef HIGHSCOREMANAGER_H_
#define HIGHSCOREMANAGER_H_

#include <map>
#include <memory>
#include "HighScoreTable.h"
#include "framework/Theme.h"

class HighScoreManager
{
private:
	std::map<std::string, std::unique_ptr<HighScoreTable>> _tableMap;
	Theme *_baseTheme;
	std::string _highScoreFile;

	void loadHighScores();
public:
	HighScoreManager();
	HighScoreManager(Theme *baseTheme);
	virtual ~HighScoreManager();

	void setBaseTheme(Theme *baseTheme) { _baseTheme = baseTheme; };

	void init();

	void release();

	HighScoreTable *createHighScoreTable(std::string tableName);
	HighScoreTable *createHighScoreTable(std::string tableName, unsigned int maxListings);

	HighScoreTable *getHighScoreTable(std::string tableName) { return _tableMap[tableName].get(); };

};

#endif /*HIGHSCOREMANAGER_H_*/
