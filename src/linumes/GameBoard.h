/***************************************************************************
 *   Copyright (C) 2006 by developer   *
 *   developer@mountain   *
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
#include <vector>

#define FROM_ORIGIN -1
#define FROM_LEFT 0
#define FROM_RIGHT 1
#define FROM_UP 2
#define FROM_DOWN 3

#define GAME_NAME "default"

namespace Linumes {
namespace HF = Hunchback::Framework;

class GameBoard : public HF::Rendered {
protected:
	//this is the name that will be registered in the highscores, descendants should define differently
	std::string _gameName;
	HighScoreTable *_hiScoreTable;

	Token _tokenSet[4];

	std::vector<GamePiece> _pieces;
	std::unique_ptr<Grid> _grid;
	std::unique_ptr<Scanner> _scanner;
	std::unique_ptr<SimpleBackground> _bg;
	std::unique_ptr<FadingForeground> _fg;
	std::unique_ptr<Icon> _icon;
	std::unique_ptr<HUD> _hud;

	MagicBlockSet _mbSet;

	//Input
	bool downpressed;
	bool leftpressed;
	bool rightpressed;

	LinumesThemeManager *themeManager;
	std::unique_ptr<HF::AudioManager> _audioManager;
	HF::Theme *currTheme;

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
	bool _midasMode;

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

	void midasLeft();
	void midasRight();

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

	HF::Theme *getTheme() { return currTheme; };

	friend class Token;
};

} // namespace Linumes

#endif
