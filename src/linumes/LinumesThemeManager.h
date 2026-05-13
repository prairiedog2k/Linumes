#ifndef LINUMESTHEMEMANAGER_H_
#define LINUMESTHEMEMANAGER_H_

#include <memory>
#include "framework/ThemeManager.h"
#include "HighScoreManager.h"

class LinumesThemeManager : public ThemeManager
{
private:
	std::unique_ptr<HighScoreManager> _highScoreManager;
public:
	LinumesThemeManager(std::string file);
	virtual ~LinumesThemeManager();
	HighScoreManager *getHighScoreManager() { return _highScoreManager.get(); };
	virtual bool init();
};

#endif /*LINUMESTHEMEMANAGER_H_*/
