#ifndef BOSSMODE_H_
#define BOSSMODE_H_

#include "linumes/GameMode.h"

namespace Linumes {

class BossMode : public GameMode
{
protected:
    virtual void createGameBoard();
public:
	BossMode();
	virtual ~BossMode();
};

} // namespace Linumes

#endif /*BOSSMODE_H_*/
