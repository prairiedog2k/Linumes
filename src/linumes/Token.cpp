#include "Token.h"
#include "SDL.h"
#include "GameBoard.h"
#include "BoardTypes.h"

Token::Token() : Block(), _brokenWait(50), _fallWait(400), _mblock(), _isActive(false) {
}

Token::Token(const Token &token) : Block((Block &)token), 
_brokenWait(50), _fallWait(400),_mblock(),_isActive(false) {

}

Token::~Token()
{

}

void Token::setTheme (Theme *theTheme) {
	_mblock.setTheme(theTheme);
	_mblock.setRenderable(true);
	for (int i = 0; i < 4; i++) {
		_pieces[i]->setTheme(theTheme);
	}  
}



void Token::Draw() {
	if (! _isActive) {
		_mblock.Draw();
	}
	for (int i = 0; i < 4; i++) {
		_pieces[i]->Draw();
	}
}



void Token::resetTokenTiming(unsigned int currTime) {
	checkBoard();

	_timerx.setInitialTime(currTime);
	_timerx.setStopped(false);
	_timerx.setWait(100);

	_pushy.setInitialTime(currTime);
	_pushy.setStopped(false);
	_pushy.setWait(37);

	_fally.setInitialTime(currTime);
	_fally.setStopped(false);
	_fally.setWait(_fallWait);

	_broken.setInitialTime(currTime);
	_broken.setStopped(false);
	_broken.setWait(_brokenWait);

	if (_leftBottom == _board->_ry) { 
		_holder.setInitialTime(currTime);
		_holder.setStopped(false);
		_holder.setWait(3000);
	}
}

void Token::init( float x, float y, float dim) {
	//dimension must be set before screen position
	setDimension(dim);
	setScreenPosition(x,y);
	setAllVisible(true);
	assignNewColors(false);  

	_mblock.setX(x+dim);
	_mblock.setY(y+dim);
	_mblock.setDim(dim);
	_mblock.setState(MagicBlock::LOOPER);
	_mblock.setMaxTime(2000);
	_mblock.start();


	_leftBottom = _board->_ry;
	_rightBottom = _board->_ry;  
	_posX = _board->_rx / 2.0f;

	resetTokenTiming(SDL_GetTicks());

	_leftLanded = false;
	_rightLanded = false;	
}

void Token::assignNewColors(bool canSpecial) {
	for (int i = 0; i < 4; i++) {		
		_pieces[i]->setNewColor( canSpecial && (i == 3) ? true : false);
	}
	if (canSpecial) {
#ifdef MING_RANDOM
		int rotCount = rand() % 4;
#else
		int rotCount = random() % 4;
#endif		
		for (int i = 0; i < rotCount; i++) {
			rotate(COUNTERCLOCKWISE);
		}
	}
}

void Token::advanceLeft(unsigned int currTime) {
	slide(LEFT, currTime);
}

void Token::advanceRight(unsigned int currTime) {
	slide(RIGHT, currTime);
}

void Token::rotate(Rotation dir) {
	int temp;
	bool btemp;
	if (dir == CLOCKWISE) {
		temp = _pieces[2]->getColor();
		_pieces[2]->setColor( _pieces[0]->getColor() );
		_pieces[0]->setColor( _pieces[1]->getColor() );
		_pieces[1]->setColor( _pieces[3]->getColor() );
		_pieces[3]->setColor( temp );
		btemp = _pieces[2]->isSpecial();
		_pieces[2]->setSpecial( _pieces[0]->isSpecial() );
		_pieces[0]->setSpecial( _pieces[1]->isSpecial() );
		_pieces[1]->setSpecial( _pieces[3]->isSpecial() );
		_pieces[3]->setSpecial( btemp );
	}
	if (dir == COUNTERCLOCKWISE) {
		temp = _pieces[2]->getColor();
		_pieces[2]->setColor( _pieces[3]->getColor() );
		_pieces[3]->setColor( _pieces[1]->getColor() );
		_pieces[1]->setColor( _pieces[0]->getColor() );
		_pieces[0]->setColor( temp );
		btemp = _pieces[2]->isSpecial();
		_pieces[2]->setSpecial( _pieces[3]->isSpecial() );
		_pieces[3]->setSpecial( _pieces[1]->isSpecial() );
		_pieces[1]->setSpecial( _pieces[0]->isSpecial() );
		_pieces[0]->setSpecial( btemp );
	}  
}

void Token::copyColors(Token token) {
	_pieces[0]->setColor( token._pieces[0]->getColor() );
	_pieces[1]->setColor( token._pieces[1]->getColor() );
	_pieces[2]->setColor( token._pieces[2]->getColor() );
	_pieces[3]->setColor( token._pieces[3]->getColor() );


	_pieces[0]->setSpecial( token._pieces[0]->isSpecial() );
	_pieces[1]->setSpecial( token._pieces[1]->isSpecial() );
	_pieces[2]->setSpecial( token._pieces[2]->isSpecial() );
	_pieces[3]->setSpecial( token._pieces[3]->isSpecial() );

}

void  Token::setAllVisible( bool visible) {
	for (int i = 0; i < 4; i++) {
		_pieces[i]->setRenderable(visible);
	}
}

void Token::setSideInvisible(int side) {
	if (side == 0) {
		_pieces[0]->setRenderable(false);
		_pieces[2]->setRenderable(false);    
	} else if (side == 1) {
		_pieces[1]->setRenderable(false);
		_pieces[3]->setRenderable(false);        
	}
}

void Token::copySideToBoard(int side) {
	checkBoard();
	int pos = (side == 0 ? -1 : 0);
	int pieceTarget = (side == 0 ?  0 : 1);
	int yTarget = (side == 0 ? _leftBottom : _rightBottom);
	_board->getPieceAt(_posX + pos, yTarget)->setColor(_pieces[pieceTarget]->getColor());
	_board->getPieceAt(_posX + pos, yTarget)->setSpecial(_pieces[pieceTarget]->isSpecial());
	_board->getPieceAt(_posX + pos, yTarget)->setRenderable(true);
	_board->getPieceAt(_posX + pos, yTarget)->setStopped(true);
	_board->getPieceAt(_posX + pos, yTarget)->setScanned(false);
	_board->getPieceAt(_posX + pos, yTarget)->setConnected(false);

	if (yTarget + 1 < _board->getRowMax()) {
		pieceTarget += 2;
		_board->getPieceAt(_posX + pos, yTarget+1)->setColor(_pieces[pieceTarget]->getColor());
		_board->getPieceAt(_posX + pos, yTarget+1)->setSpecial(_pieces[pieceTarget]->isSpecial());
		_board->getPieceAt(_posX + pos, yTarget+1)->setRenderable(true);
		_board->getPieceAt(_posX + pos, yTarget+1)->setStopped(true);
		_board->getPieceAt(_posX + pos, yTarget+1)->setScanned(false);
		_board->getPieceAt(_posX + pos, yTarget+1)->setConnected(false);
	}
	setSideInvisible(	side );
}

bool Token::canDrop(int currTime) {
	//if it's broken we check the wait for broken pieces
	if (( _leftLanded || _rightLanded) && (_broken.canMove(currTime))) {
		return true;
	}

	//if it's whole and free falling (and the holder has expired)
	if (_fally.canMove(currTime) && _holder.canMove(currTime)) {
		return true;
	}

	//if the user is actively pressing downward and the push expiration has expired 
	if ( (_board->downpressed) && (_pushy.canMove(currTime) && ( isWhole() ) ) ){
		//add 1 point for each level forcibly descended
		_board->addToScore(1);
		return true;
	}

	return false;
}

void Token::update(unsigned int currTime) {
	if (_mblock.isComplete()) {
		_mblock.start();
	}
	if ( ! _isActive) {
		return;
	}

	checkBoard();

	if (!canDrop(currTime)) {
		return;
	}
	//reset the gravity and drop timers
	//holder is only reset on init.
	_fally.setInitialTime(currTime);
	_pushy.setInitialTime(currTime);
	_broken.setInitialTime(currTime);
	_holder.setWait(0);



	if (!_leftLanded) {
		if ((_leftBottom - 1) >= 0) {
			if ( ! _board->getPieceAt(_posX-1, _leftBottom - 1)->isRenderable() ) {
				_leftBottom--;
			} else {
				copySideToBoard(0);
				_leftLanded = true;
			}
		} else if (_leftBottom == 0) {
			copySideToBoard(0);	
			_leftLanded = true;	
		}
	}

	if (!_rightLanded) {
		if ((_rightBottom - 1) >= 0) {
			if ( ! _board->getPieceAt(_posX, _rightBottom - 1)->isRenderable() ) {
				_rightBottom--;
			} else {
				copySideToBoard(1);
				_rightLanded = true;
			}
		} else if (_rightBottom == 0) {
			copySideToBoard(1);
			_rightLanded = true;
		}
	}

	//advance
	setY(getY() - getDimension());

	if (_leftLanded || _rightLanded) {
		if (_leftLanded) {
			_board->updateSpecialAt(_posX -1, _leftBottom +1);
			_board->updateSpecialAt(_posX -1, _leftBottom);
		}
		if (_rightLanded) {
			_board->updateSpecialAt(_posX, _leftBottom +1);
			_board->updateSpecialAt(_posX, _leftBottom);
		}
		_board->_audioManager->playSoundEffect(AUDIO_DROP); 
	}


	if ( _leftLanded && _rightLanded) {
		if ((_leftBottom >= _board->_ry) || (_rightBottom >= _board->_ry)) {
#ifdef DEBUG
			std::cout << "Game Should Be Over " << endl;
#endif
			_board->setGameOver(true);
		}
	}
}

void Token::slide(Slide dir, unsigned int currTime) {
	checkBoard();
	int mult = (dir == RIGHT ? 1 : -1);
	int nextXPos = _posX + mult;
	//can't move a broken token
	if (_leftLanded || _rightLanded) {
		return;
	}
	//can't move before our wait period expires
	if (!_timerx.canMove( currTime ) ){
		return;
	}
	if ((nextXPos > 0) && (nextXPos < _board->_rx)) {
		if (_leftBottom >= _board->_ry) {
			setX( getX() + (float)(mult * _dim) );
			_posX = nextXPos;
			_timerx.setInitialTime( currTime );

		} else {
			if ( _leftBottom + 1 < _board->getRowMax() ) {
				if ( ( _board->getPieceAt( ( (mult < 0) ? (nextXPos - 1): nextXPos ) , _leftBottom )->isRenderable() ) || 
						( _board->getPieceAt( ( (mult < 0) ? (nextXPos - 1): nextXPos ) , _leftBottom + 1 )->isRenderable() )	) {
					return;
				} 
			} else {
				if ( _board->getPieceAt( ( (mult < 0) ? (nextXPos - 1): nextXPos ) , _leftBottom )->isRenderable() ) {  
					return;				
				}				 
			}
			setX( getX() + (float)(mult * _dim) );
			_posX = nextXPos;
			_timerx.setInitialTime(currTime);
		}

		_board->_audioManager->playSoundEffect(AUDIO_MOVE); 
	}
}

void Token::dump() {
#ifdef DEBUG
		std::cout << "------" << endl;
		std::cout << "|" << (_pieces[0]->isSpecial() ? "T" : "F") << "|"<< (_pieces[1]->isSpecial() ? "T" : "F") << "|" << "|" << (_pieces[0]->getColor()) << "|"<< (_pieces[1]->getColor()) << "|" << endl;
		std::cout << "------" << endl;
		std::cout << "|" << (_pieces[2]->isSpecial() ? "T" : "F") << "|"<< (_pieces[3]->isSpecial() ? "T" : "F") << "|" << "|" << (_pieces[2]->getColor()) << "|"<< (_pieces[3]->getColor()) << "|" << endl;
		std::cout << "------" << endl;
#endif
	}
