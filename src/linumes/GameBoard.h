/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GamePiece.h"
#include "framework/Rendered.h"
#include "framework/Theme.h"
#include "LinumesThemeManager.h"
#include "framework/AudioManager.h"
#include "Grid.h"
#include "HUD.h"
#include "Scanner.h"
#include "SimpleBackground.h"
#include "FadingForeground.h"
#include "HighScoreTable.h"
#include "Rotation.h"
#include "Token.h"
#include "Icon.h"
#include "MagicBlock.h"
#include <memory>

#define FROM_ORIGIN -1
#define FROM_LEFT 0
#define FROM_RIGHT 1
#define FROM_UP 2
#define FROM_DOWN 3

#define GAME_NAME "default"

class GameBoard : public Rendered {
protected:
	//this is the name that will be registered in the highscores, descendants should define differently
	std::string _gameName;
	HighScoreTable *_hiScoreTable;
	
	Token _tokenSet[4];

	GamePiece *_pieces;
	Grid *_grid;
	Scanner  *_scanner;
	auto_ptr<SimpleBackground> _bg;
	auto_ptr<FadingForeground> _fg;
	auto_ptr<Icon>  _icon;  
	auto_ptr<HUD> _hud;

	MagicBlockSet _mbSet;
	
	//Input
	bool downpressed;
	bool leftpressed;
	bool rightpressed;	  

	LinumesThemeManager *themeManager;
	AudioManager *_audioManager;
	Theme *currTheme;

	float _dim;
	int _rx;
	int _ry ;
	int _targetCount;
	int lastscanned;	

	bool _advanceScanner;
	
	//game time to be reported in seconds
	unsigned int _gameTime;
	unsigned int _pauseTime;
	
	bool _isThemeChanging;		
	//score to report in units of 10
	bool _gameOver;
	
	int _tokenCount;
	int _pieceCount;
	int _blockCount;
	int _totalBlockCount;
	int _high;
	int _score;
	bool _canBonus;
	bool _scoreChecked;
	
	unsigned int _currentTick;
	unsigned int _announceTime;
	
	virtual GamePiece *getPieceAt( int x, int y);

	void drawPieces();
	void drawGrid();
	void drawScanner();	
	void drawBackground();
	void drawScoreTargets();
	void drawTokens();
	void drawIcon();
	void drawHud();
	void drawMagicBlocks();
	void drawForeground();

	int scanTo(int column);
	//method for subclasses to render additional content
	virtual void evaluateBonus();
	virtual void checkHighScore();
	virtual void cleanScanned(int column);
	virtual void dropPieces();
	virtual void assignInitialTheme();
	
	virtual void updateContents();
	//called to reset individual members in a subclass after a scanner pass
	virtual void resetContents();
	
	virtual void updateHud();	
	virtual void drawContents();
	
	
	void resetScan();

	virtual void markScoreTargets();

	void createTokenSet(int tokenPos);
	
	//input events		
	void rotateToken( Rotation dir);
	void updateToken();

	float getLevelFallRate();
	void setPieceInMotion(int i, int j);
	void applyNextTheme();
public:
	GameBoard( float dim, int rx, int ry);
	virtual ~GameBoard();
	virtual void init(); 
	virtual void reset(); 
	void dump();

	virtual void update(unsigned int currTick);
	virtual void Draw();

	void setThemeManager(LinumesThemeManager *tm) { themeManager = tm; };

	void changeTheme();

	//input events
	void LeftKeyDown(){leftpressed = true;};
	void RightKeyDown(){rightpressed = true;};
	void DownKeyDown(){ downpressed = true;};
	void LeftKeyUp(){leftpressed = false;};
	void RightKeyUp(){rightpressed = false;};
	void DownKeyUp(){downpressed = false;};
	void RotateLeft() { if (!_gameOver) { rotateToken(CLOCKWISE); } };
	void RotateRight(){ if (!_gameOver) { rotateToken(COUNTERCLOCKWISE); } };  

	int getRowMax() { return _ry; };
	int getColMax() { return _rx; };
	
	void updateSpecialAt (int x, int y);

	virtual void toggleScanner(unsigned int currTime);
	void advanceToken();  
	void updateTokens();
	void markSpecial(int x, int y);
	bool isGameOver() { return _gameOver; };
	void setGameOver( bool gameOver) { _gameOver = gameOver; if (_gameOver) { _audioManager->stopSong(); } };
	
	//score
	int getHigh() { return _high; };
	
	int getScore() { return _score; };
	int getBlockCount() { return _blockCount; };	

	void setScore(int score) { _score = score; };
	void setBlockCount (int count) { _blockCount = count; };
	
	void addToScore(int score) { _score += score; };
	virtual void addToBlockCount (int count) { _blockCount += count; };	
	
	unsigned int getCurrentGameTime();
	
protected:
	float getMinX();
	float getMaxX();
	float getMinY();
	float getMaxY();
	float getPieceX(int i);
	float getPieceY(int j);

	//scanner
	float calculateRate(float ScanTime);
	
	Theme *getTheme() { return currTheme; };
	
	friend class Token;
};
#endif
