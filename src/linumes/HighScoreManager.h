#pragma once

#include <map>
#include <memory>
#include "HighScoreTable.h"
#include "framework/Theme.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class HighScoreManager
{
private:
	std::map<std::string, std::unique_ptr<HighScoreTable>> _tableMap;
	HF::Theme *_baseTheme;
	std::string _highScoreFile;

	void loadHighScores();
public:
	HighScoreManager();
	HighScoreManager(HF::Theme *baseTheme);
	virtual ~HighScoreManager();

	void setBaseTheme(HF::Theme *baseTheme) { _baseTheme = baseTheme; };

	void init();

	void release();

	HighScoreTable *createHighScoreTable(std::string tableName);
	HighScoreTable *createHighScoreTable(std::string tableName, unsigned int maxListings);

	HighScoreTable *getHighScoreTable(std::string tableName) { return _tableMap[tableName].get(); };

};

} // namespace Hunchback::Linumes
