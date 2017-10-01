#ifndef LINUMESTHEMEMANAGER_H_
#define LINUMESTHEMEMANAGER_H_

#include "framework/ThemeManager.h"
#include "HighScoreManager.h"

class LinumesThemeManager : public ThemeManager
{
private:
	HighScoreManager *_highScoreManager;
public:
	LinumesThemeManager(std::string file);
	virtual ~LinumesThemeManager();
	HighScoreManager *getHighScoreManager() { return _highScoreManager; };
	virtual bool init();
};

#endif /*LINUMESTHEMEMANAGER_H_*/
