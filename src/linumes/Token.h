#ifndef TOKEN_H_
#define TOKEN_H_

#include "Block.h"
#include "framework/Timed.h"
#include "Rotation.h"
#include "Slide.h"
#include "MagicBlock.h"
#include <cassert>

using namespace std;

class GameBoard;

class Token : public Block
{
protected:
	//how fast we can advance the token left or right
	Timed _timerx;  

	//how fast we can advance the token downward
	Timed _pushy;  

	//how fast a non-broken token drops
	Timed _fally;

	//how long can we stay at the top of the screen
	Timed _holder;

	//how fast a broken token drops
	Timed _broken;

	//tokens horizontal position on the board
	// _posX - 1 is the left block
	// _posX is the right block
	int _posX;

	//the vertical position of the token's left side on the board
	int _leftBottom;

	//the vertical position of the token's right side on the board
	int _rightBottom;

	//so we can get board data easily (we are a 'friend' of GameBoard).
	GameBoard *_board;

	//indicators for which side of the token is stationary 
	bool _leftLanded;
	bool _rightLanded;

	//configurable values for how long to wait until advancing either in a 
	// broken state	
	int _brokenWait;
	//or a whole state
	int _fallWait;	
	
	MagicBlock _mblock;
	bool _isActive;
public:
	Token();
	Token(const Token &token);
	virtual ~Token();
	virtual void Draw();
	void advanceLeft(unsigned int currTime);
	void advanceRight(unsigned int currTime);
	void resetTokenTiming(unsigned int currTime);
	void setFallWait(int fallwait) { _fallWait = fallwait; };
	void setBrokenWait(int brokenwait) { _brokenWait = brokenwait; };
	void setTheme (Theme *theTheme);
	void init( float x, float y, float dim);
	void update(unsigned int currTime);
	void setSideInvisible( int side );
	void copySideToBoard( int side );
	void setAllVisible( bool visible);
	void rotate(Rotation dir);
	void copyColors(Token token);
	void assignNewColors(bool canSpecial);
	void setBoard(GameBoard *board) { _board = board; };
	void setActive(bool active) { _isActive = active; };
	void dump();
private:
	void checkBoard() { assert(_board); };
	void slide(Slide dir, unsigned int currTime);
	bool canDrop(int currTime);  	
	void drop();
};

#endif /*TOKEN_H_*/
