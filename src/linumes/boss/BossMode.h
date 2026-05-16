#pragma once

#include "linumes/GameMode.h"

namespace Hunchback::Linumes {

class BossMode : public GameMode
{
protected:
    virtual void createGameBoard();
public:
	BossMode();
	virtual ~BossMode();
};

} // namespace Hunchback::Linumes
