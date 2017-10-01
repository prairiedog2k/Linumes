#ifndef BOSSBOARD_H
#define BOSSBOARD_H

#include "linumes/GameBoard.h"
#include "Boss.h"
#include "BossPiece.h"
#include "BossIcon.h"

class BossBoard : public GameBoard {
private:
    Boss _boss;   
    BossPiece *_bossPieces;
    auto_ptr<BossIcon>  _bossIcon;
    int _bossAttacks;
    
    unsigned int _attackStart;
    unsigned int _attackDuration;
    bool _bossWinPlayed;
    bool isAttacking() { return _currentTick - _attackStart < _attackDuration; }    
    void drawAttack();
    void drawGameOver();
protected:
	virtual GamePiece *getPieceAt( int x, int y);
	virtual void cleanScanned(int column);
	virtual void dropPieces();
	virtual void assignInitialTheme();
	virtual void drawContents();
	virtual void updateContents();
	virtual void resetContents();
	virtual void updateHud();
	virtual void evaluateBonus();
public:
    BossBoard();
    virtual ~BossBoard();    
   	virtual void init();
   	virtual void reset();
   	virtual void addToBlockCount (int count);
};

#endif
