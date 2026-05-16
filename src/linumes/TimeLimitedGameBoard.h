#pragma once

#include "GameBoard.h"
#include "framework/TextureQuad.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class TimeLimitedGameBoard : public GameBoard
{
private:
	unsigned int _gameDuration;
	bool _timeOver;
	HF::TextureQuad _quad;
public:
	TimeLimitedGameBoard();
	TimeLimitedGameBoard(unsigned int gameDuration);
	virtual ~TimeLimitedGameBoard();
	virtual void update(unsigned int currTick);
	virtual void reset();
protected:
	virtual void updateHud();
	virtual void drawContents();
	virtual void checkHighScore();
	virtual void evaluateBonus() { }; //do not evaluate bonus
};

} // namespace Hunchback::Linumes
