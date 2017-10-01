#ifndef BOSSMODE_H_
#define BOSSMODE_H_

#include "linumes/GameMode.h"

class BossMode : public GameMode
{
protected:
    virtual void createGameBoard(); 
public:
	BossMode();
	virtual ~BossMode();
};

#endif /*BOSSMODE_H_*/
