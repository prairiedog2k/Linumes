/*   Copyright (C) 2006 by developer   *
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
#include <iostream>
#include <cassert>
#include "SDL.h"
#include "GL/gl.h"
#include "GL/glu.h"

#include "GameBoard.h"
#include "Block.h"
#include <string>
#include "BoardTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"

#include "HighScoreManager.h"

#ifdef DEBUG
#define glError() { \
        GLenum err = glGetError(); \
        while (err != GL_NO_ERROR) { \
                fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
                err = glGetError(); \
        } \
}
#else
#define glError()
#endif

#define BASE_FONT_12 "base_font_12" 


/**
 * Conventions:
 * Grid is Cartesian.
 *
 * Grid x   0 -> rx -1 (increasing left to right)
 *
 * Grid y   ry -1  (increasing bottom to top)
 *           ^
 *           |
 * 			 0
 *
 * Token positions 0 - 2 on vert. centered on the side.
 * 3 is above and horiz. centered on the Piece Grid
 * 0 fills from the bottom
 *                   3
 *		   ______________________
 *  ____   |_|_|_|_|_|_|_|_|_|_|_|
 *  |_|_|  |_|_|_|_|_|_|_|_|_|_|_|
 * 2|_|_|  |_|_|_|_|_|_|_|_|_|_|_|
 *  |_|_|  |_|_|_|_|_|_|_|_|_|_|_|
 * 1|_|_|  |_|_|_|_|_|_|_|_|_|_|_| 
 *  |_|_|  |_|_|_|_|_|_|_|_|_|_|_|
 * 0|_|_|  |_|_|_|_|_|_|_|_|_|_|_|
 *         |_|_|_|_|_|_|_|_|_|_|_|
 */

GameBoard::GameBoard( float dim, int rx, int ry):
	Rendered(true),
	_hiScoreTable(NULL),
	_scanner(new Scanner( (float) - ( (rx * dim)  / 2.0f ),
			(float)rx*dim - ( (rx * dim)  / 2.0f ),
			(float)ry*dim - ( (ry * dim)  / 2.0f ),
			1.0 ,
			dim,
			(float)ry * dim,
			rx)),
			_bg( new SimpleBackground(0.0,0.0) ),
			_fg( new FadingForeground(0.0,0.0,1000)),
			_icon( new Icon() ),
			_hud( new HUD() ),
			currTheme(NULL),
			_isThemeChanging(false),
			_gameOver(false),
			_tokenCount(0),
			_pieceCount(0),
			_blockCount(0),
			_totalBlockCount(0),
			_high(0),
			_score(0),			
			_canBonus(false),
			_scoreChecked(false),
			_midasMode(false) {
	downpressed = false;
	leftpressed = false;
	rightpressed = false;
	_advanceScanner = true;
	_dim = dim;
	_rx = rx;
	_ry = ry; 

	_pieces = new GamePiece[ _rx * _ry];

	_grid = new Grid(0.0,0.0,dim,rx,ry);
	_grid->setRenderable(true);

	_icon->setRenderable(true);

	_scanner->setStopped(false);
	_scanner->setXRate(calculateRate(5.0f));
	lastscanned = 0;
	_audioManager = new AudioManager();
	_currentTick = SDL_GetTicks();
	_gameTime = _currentTick;
	_gameName = GAME_NAME;
}

//given a time in seconds that you want to scan the board in
//this will provide the scanner with the appropriate rate for
// the size of the board
float GameBoard::calculateRate(float ScanTime) {
	if ( ScanTime == 0.0f ) {
		return 0.0f;
	}
	float distance = _rx * _dim;
	float scanRate = ( distance / 1000.0f);
	float frequency = 1.0f / (float)ScanTime;
	return frequency * scanRate;
}


float GameBoard::getMinX() {
	return  (float) - ( (_rx * _dim)  / 2.0f );
}

float GameBoard::getMaxX() {
	return (float)_rx*_dim - ( (_rx * _dim)  / 2.0f );
}

float GameBoard::getMinY() {
	return  (float) - ( (_ry * _dim)  / 2.0f );
}

float GameBoard::getMaxY() {
	return (float)_ry*_dim - ( (_ry * _dim)  / 2.0f );
}


GameBoard::~GameBoard()
{
	if (_pieces != NULL)
	{
		delete[] _pieces;
	}

	if (_grid != NULL) {
		delete _grid;
	}

	if (_audioManager != NULL) {
		delete _audioManager;
	}
	
	if (_scanner != NULL) {
		delete _scanner;
	}

	/*  The following members are std::auto_ptr and do not need to be deleted
	// _hud
	// _bg
	// _icon
	
	 */

	_mbSet.clear();
}

GamePiece *GameBoard::getPieceAt( int x, int y)
{
	int pos =(  x * _ry ) + y;
	return 	&_pieces[pos];
}

void GameBoard::createTokenSet(int tokenPos) {
	float leftMostX = getMinX() - 2.5f * _dim;
	float bottomMostY = (-4.0f * _dim) + (tokenPos * 2.0f * (_dim +  (_dim / 2.0f)));

	if (tokenPos == 3) {
		float halfway =  _rx / 2.0f;
		float distance = (float) halfway * _dim;
		distance += getMinX();
		distance -= _dim;
		leftMostX = distance;
		bottomMostY = getMaxY();
	}

	float y0 = bottomMostY;
	float x0 = leftMostX;

	_tokenSet[tokenPos].setBoard(this);
	_tokenSet[tokenPos].setActive( tokenPos == 3 );
	_tokenSet[tokenPos].init(x0,y0, (tokenPos == 3 ? _dim : _dim/1.25f) );

	_tokenSet[tokenPos].setTheme(currTheme);

}

void GameBoard::assignInitialTheme() {
	if (currTheme == NULL)
	{
		currTheme = themeManager->getCurrentTheme();
	}
}

void GameBoard::init()
{
	assignInitialTheme();

	_audioManager->init();
	_grid->setAudioManager(_audioManager);
	
	_icon->setDimension(3 * _dim);
	_icon->setX(getMinX() - 2.90 * _dim);
	_icon->setY(getMinY() - 2.90 * _dim);
	
	for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{   
			getPieceAt(i,j)->setNewColor();
			getPieceAt(i,j)->setStopped( false );
			getPieceAt(i,j)->setDimension( _dim);
			getPieceAt(i,j)->setPiecePos (getPieceX(i),getPieceY(j));
			getPieceAt(i,j)->setNextY( getPieceY(j) );
			getPieceAt(i,j)->setTheme( currTheme );
			getPieceAt(i,j)->setRenderable(false);
		}
	}

	if (currTheme != NULL) {
		_audioManager->setTheme(currTheme);
		_audioManager->playSong(AUDIO_SONG);
		_grid->setTheme(currTheme);
		_scanner->setTheme(currTheme);
		_bg->setTheme(currTheme);
		_icon->setTheme(currTheme);
		_hud->setTheme(currTheme);
		_fg->setTheme(currTheme);
	}

	std::string artist = _audioManager->getArtist();
	std::string track =  _audioManager->getTrack();
	std::string displayInfo = artist + " - " + track;

	_fg->setDisplayInfo(displayInfo);

	_fg->start();

	HighScoreManager *hsm = themeManager->getHighScoreManager();
	_hiScoreTable = hsm->getHighScoreTable(_gameName);
	if (NULL == _hiScoreTable) {
		_hiScoreTable = hsm->createHighScoreTable(_gameName);
	}
	_high = _hiScoreTable->getHighestScore();

	for (int i = 0; i < 4; i++) {
		createTokenSet( i );
	}
}

float GameBoard::getPieceX(int i) {
	return (float)i*_dim - ( (_rx * _dim)  / 2.0f );
}

float GameBoard::getPieceY(int j) {
	return (float)j*_dim - ( (_ry * _dim)  / 2.0f );
}

void GameBoard::reset() {
	if (isGameOver()) {
		_gameOver = false;
	
		delete _scanner;
		_scanner = new Scanner( (float) - ( (_rx * _dim)  / 2.0f ),
								(float)_rx*_dim - ( (_rx * _dim)  / 2.0f ),
								(float)_ry*_dim - ( (_ry * _dim)  / 2.0f ),
								1.0 ,
								_dim,
								(float)_ry * _dim,
								_rx);
		_scanner->setStopped(false);
		_scanner->setXRate(calculateRate(5.0f));
		_scanner->setTheme(currTheme);
		
		_audioManager->setTheme(currTheme);
		_audioManager->playSong(AUDIO_SONG);
		
		_mbSet.clear();
		
		_tokenCount = 0;
		_pieceCount = 0,
		_blockCount = 0;
		_totalBlockCount = 0;
		_score = 0;		
		_scoreChecked = false;
		
		_currentTick = SDL_GetTicks();
		_gameTime = _currentTick;
		
		toggleScanner(_currentTick);
		
		for (int i = 0; i < _rx; i++) {	
			for (int j = (_ry - 1) ; j >= 0; j--) {
				getPieceAt(i,j)->setNewColor();
				getPieceAt(i,j)->setScanned(false);
				getPieceAt(i,j)->setScoreTarget(false);
				getPieceAt(i,j)->setStopped( false );
				getPieceAt(i,j)->setDimension( _dim);
				getPieceAt(i,j)->setPiecePos ( getPieceX(i) , getPieceY(j) );
				getPieceAt(i,j)->setNextY( getPieceY(j) );
				getPieceAt(i,j)->setTheme( currTheme );
				getPieceAt(i,j)->setRenderable(false);
			}
		}	
		advanceToken();
		
		std::string artist = _audioManager->getArtist();
		std::string track =  _audioManager->getTrack();
		std::string displayInfo = artist + " - " + track;

		_fg->setDisplayInfo(displayInfo);
		_fg->setFade(FADE_IN);
		_fg->start();
	}
}

//called to reset individual members in a subclass after a scanner pass
void GameBoard::resetContents() {
	
}

void GameBoard::toggleScanner(unsigned int currTime) {

	_advanceScanner = (!_advanceScanner);

	if (_advanceScanner) {
		_tokenSet[3].resetTokenTiming(currTime);
		_gameTime = _currentTick - _pauseTime;
	} else {
		_pauseTime = _currentTick - _gameTime;
	}
	_scanner->togglePause();
};

void GameBoard::applyNextTheme()
{
	Theme *nextTheme = NULL;
	if (themeManager != NULL)
	{
		nextTheme = themeManager->getNextTheme();
	}

	for (int i = 0; i < 4; i++){
		_tokenSet[i].setTheme(nextTheme);
	}

	/* Apply theme to themed objects */
	//pieces
	for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{
			getPieceAt(i,j)->setTheme( nextTheme );
		}
	}


	//grid
	_grid->setTheme( nextTheme);

	//scanner
	_scanner->setTheme (nextTheme);

	//bg
	_bg->setTheme(nextTheme);

	//icon
	_icon->setTheme(nextTheme);

	//hud
	_hud->setTheme(nextTheme);

	//audioManager
	_audioManager->setTheme(nextTheme);

	_audioManager->playSong(AUDIO_SONG);

	_fg->setTheme(nextTheme);

	std::string artist = _audioManager->getArtist();
	std::string track =  _audioManager->getTrack();
	std::string displayInfo = artist + " - " + track;

	_fg->setDisplayInfo(displayInfo);


	for ( std::set<MagicBlock>::iterator iter = _mbSet.begin(); iter != _mbSet.end(); iter++) {
		((MagicBlock)*iter).setTheme(nextTheme);
	}

	currTheme = nextTheme;
}

void GameBoard::drawPieces()
{
	for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{
			getPieceAt(i,j)->Draw();
		}
	}
}


void GameBoard::drawTokens() {
	for (int i = 0; i < 4; i++) {
		_tokenSet[i].Draw();
	}
}

void GameBoard::drawGrid() {
	_grid->Draw();
}

void GameBoard::drawIcon() {
	_icon->Draw();
}


void GameBoard::markSpecial(int x, int y) {
	getPieceAt(x,y)->setConnected(true);
	getPieceAt(x,y)->setScoreTarget(true);
	if (x > 0) {
		if (  getPieceAt(x-1,y)->isRenderable() &&
				!getPieceAt(x-1,y)->isConnected() &&
				( getPieceAt(x-1,y)->getColor() == getPieceAt(x,y)->getColor() ) )  {
			markSpecial(x-1,y);
		}
	}

	if (x < _rx - 1) {
		if (  getPieceAt(x+1,y)->isRenderable() &&
				!getPieceAt(x+1,y)->isConnected() &&
				( getPieceAt(x+1,y)->getColor() == getPieceAt(x,y)->getColor() ) ) {
			markSpecial(x+1,y);
		}
	}

	if (y > 0) {

		if (  getPieceAt(x,y-1)->isRenderable() &&
				!getPieceAt(x,y-1)->isConnected() &&
				( getPieceAt(x,y-1)->getColor() == getPieceAt(x,y)->getColor() ) ) {
			markSpecial(x,y-1);
		}
	}

	if (y < _ry -1) {
		if (  getPieceAt(x,y+1)->isRenderable() &&
				!getPieceAt(x,y+1)->isConnected() &&
				( getPieceAt(x,y+1)->getColor() == getPieceAt(x,y)->getColor() ) ) {
			markSpecial(x,y+1);
		}
	}
}

void GameBoard::drawScoreTargets() {
	for (int i = 0; i < _rx-1; i++)
	{
		for (int j = 1; j < _ry ; j++)
		{
			Block block(
					getPieceAt(i,j),
					getPieceAt(i+1,j),
					getPieceAt(i,j-1),
					getPieceAt(i+1,j-1));

			MagicBlock mb(0.0f,0.0f,0.0f,(j *_rx) + i);

			std::set<MagicBlock>::iterator pos = _mbSet.find(mb);

			if (block.isScoreTarget()) {
				block.setTheme(currTheme);
				block.Draw();
			} else {
				if ( ! (pos == _mbSet.end() ) ){
					if (( MagicBlock::SPARK == ((MagicBlock)*pos).getState() ) && ((MagicBlock)*pos).isComplete()) {
						MagicBlock mb(((MagicBlock)*pos).getX(),((MagicBlock)*pos).getY(),((MagicBlock)*pos).getDim(),((MagicBlock)*pos).getBoardPos());
						_mbSet.erase( ((MagicBlock)*pos) );
						mb.setState(MagicBlock::STAR);
						mb.setMaxTime(250);
						mb.start();
						_mbSet.insert(mb);
					} else {
						if (((MagicBlock)*pos).isComplete()) {
							_mbSet.erase( ((MagicBlock)*pos) );
							//There was score target here and now it's gone
							//increment the block count;
							addToBlockCount(1);
							_audioManager->playSoundEffect(AUDIO_SCAN);
						}
					}
				}
			}
		}

	}
}



void GameBoard::drawMagicBlocks() {
	for ( std::set<MagicBlock>::iterator iter = _mbSet.begin(); iter != _mbSet.end(); iter++) {
		MagicBlock mb = (MagicBlock)*iter;
		if ( ! mb.isComplete() ) {
			mb.setTheme(currTheme);
			mb.Draw();
		}
	}
}

void GameBoard::drawScanner() {
	if ( ! _gameOver ) {
		_scanner->Draw();
	}
}

void GameBoard::drawBackground() {
	_bg->Draw();
}

void GameBoard::drawHud() {
	_hud->Draw();
}

void GameBoard::drawForeground() {
	_fg->Draw();
}

void GameBoard::drawContents() {
	drawBackground();

	drawGrid();

	drawPieces();

	drawTokens();

	drawScoreTargets();

	drawMagicBlocks();

	drawScanner();

	drawForeground();

	drawIcon();

	drawHud();	
}

void GameBoard::Draw()
{
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity( );
	glTranslatef( 0.0f, 0.0f, -10.0f );

	drawContents();

	/* Draw it to the screen */
	glError();
	
	SDL_GL_SwapBuffers( );
}

int GameBoard::scanTo(int column) {
	int targetCount = 0;
	if (column < _rx) {
		for (int j = _ry - 1; j >= 0; j--)
		{

			if (getPieceAt(column,j)->isScoreTarget()) {
				getPieceAt(column,j)->setScanned(  true );
				targetCount++;

				MagicBlock mb(0.0f,0.0f,0.0f,(j *_rx) + column);

				std::set<MagicBlock>::iterator pos = _mbSet.find(mb);
				if ( ! (pos == _mbSet.end() ) ){
					if (  MagicBlock::SHRINKER == ((MagicBlock)*pos).getState() ) {
						MagicBlock mb(((MagicBlock)*pos).getX(),((MagicBlock)*pos).getY(),((MagicBlock)*pos).getDim(),((MagicBlock)*pos).getBoardPos());
						_mbSet.erase( ((MagicBlock)*pos) );
						mb.setState(MagicBlock::SPARK);
						mb.setMaxTime(500);
						mb.start();
						_mbSet.insert(mb);
					}
				}
			}
		}
	}
	return targetCount;
}

void GameBoard::markScoreTargets() {
	//all older connections need to be invalidated.
	//we will be creating valid connections during this pass
	for (int i = 0; i < _rx; i++)
	{
		for (int j = 0; j < _ry ; j++)
		{
			getPieceAt(i,j)->setConnected(false);
		}
	}

	for (int i = 0; i < _rx-1; i++)
	{
		for (int j = 1; j < _ry ; j++)
		{
			Block block( getPieceAt(i,j),
					getPieceAt(i+1,j),
					getPieceAt(i,j-1),
					getPieceAt(i+1,j-1));

			if (block.isScoreTarget()) {
				getPieceAt(i  ,j  )->setScoreTarget(true);
				getPieceAt(i+1,j  )->setScoreTarget(true);
				getPieceAt(i  ,j-1)->setScoreTarget(true);
				getPieceAt(i+1,j-1)->setScoreTarget(true);

				//TODO: make sure that scan does not remove if
				//score targets are in the next column
				//mark special -
				int x = -1;
				int y = -1;
				if (block.hasSpecial(x,y)) {
					markSpecial(i + x, j - y);
				}

				MagicBlock mb(getPieceAt(i+1,j)->getX(),getPieceAt(i+1,j)->getY(),_dim,(j * _rx) + i);
				mb.setState(MagicBlock::SHRINKER);
				mb.setMaxTime(750);
				mb.start();
				_mbSet.insert(mb);
			}
		}
	}
}

float GameBoard::getLevelFallRate() {
	return -0.005f;
}

void GameBoard::setPieceInMotion(int i, int j) {
	//lower piece can move and be rendered
	getPieceAt(i,j-1)->setStopped(false);
	getPieceAt(i,j-1)->setInitialTime(_currentTick);
	getPieceAt(i,j-1)->setYRate( getLevelFallRate() );

	//calculate the absolute Y position for this piece and subtract
	//the height attributable to the number of pieces that don't exist beneath this piece

	//the initial y for the given block
	float yInitial = ( (float)(j) *_dim);
	//centering
	yInitial -= ( ( (float) (_ry * _dim) ) / 2.0f );

	//the final y position for this block
	float yFinal = ( (float)(j - 1) *_dim);
	//centering
	yFinal -= ( (float)(_ry * _dim) / 2.0f );

	getPieceAt(i,j-1)->setNextY( yFinal );
	getPieceAt(i,j-1)->setY( yInitial  );
}

void GameBoard::dropPieces() {
	for (int i = 0; i < _rx; i++) {
		for (int j = _ry - 1 ;  j > 0; j--) {
			//for (int j = 1 ;  j  < _ry; j++) {
			if ( !getPieceAt(i,j-1)->isRenderable() &&
					getPieceAt(i,j-1)->isStopped() &&
					getPieceAt(i,j  )->isRenderable() )  {

				//set default state
				getPieceAt(i,j)->setScanned(false);
				getPieceAt(i,j)->setConnected(false);
				getPieceAt(i,j)->setScoreTarget(false);

				//copy state (color, etc.) from upper piece into lower piece
				getPieceAt(i,j-1)->copyPieceState(getPieceAt(i,j));
				//set the lower piece in motion using information from the upper piece
				//specifically, its height.
				setPieceInMotion(i,j);

				//swap visibility
				getPieceAt(i,j-1)->setRenderable(true);
				getPieceAt(i,j)->setRenderable(false);
			}
		}
	}
}

void GameBoard::cleanScanned(int column) {
	//don't erase all the Sets on the board
	if ((column < _rx) && (lastscanned < _rx)) {
		for (int i = lastscanned; i <= column ; i++)
		{
			for (int j = _ry - 1; j >= 0; j--)
			{
				if ( getPieceAt(i,j)->isScanned() )
				{
					getPieceAt(i,j)->setRenderable(false);
					getPieceAt(i,j)->setScanned( false );
					_canBonus = true;
				}

				lastscanned = column + 1;
				if (lastscanned >= _rx) {
					lastscanned = 0;
				}
			}
		}
		for (int i = 0; i < lastscanned; i++) {
			for (int j = _ry - 1; j >= 0; j--) {
				if (getPieceAt(i,j)->isRenderable() ) {
					getPieceAt(i,j)->setScanned(false);
				}
			}
		}
	}
	evaluateBonus();
}

void GameBoard::evaluateBonus() {
	if (_canBonus) {
		bool allColor0 = true;
		bool allColor1 = true;
		bool allInvisible = true;
		for (int i = 0; i < _rx; i++) {
			for (int j = 0; j < _ry; j++) {
				if (getPieceAt(i,j)->isRenderable()) {
					allInvisible = false;
				}
				if ((getPieceAt(i,j)->isRenderable()) && (getPieceAt(i,j)->getColor() == 0)) {
					allColor1 = false;
				}
				if ((getPieceAt(i,j)->isRenderable()) && (getPieceAt(i,j)->getColor() == 1)) {
					allColor0 = false;
				}
			}
		}
		if ( (allColor0) || (allColor1) ){
			_announceTime = _currentTick;
			_hud->setValue("announce","Single Color Bonus 1K");
			addToScore(1000);
		}
		if (allInvisible) {
			_announceTime = _currentTick;
			_hud->setValue("announce","All Clear Bonus 10K");			
			addToScore(10000);
		}
		_canBonus = false;
	}
}

void GameBoard::resetScan() {
	_gameOver = false;
	for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{
			getPieceAt(i,j)->setScanned( false);
			getPieceAt(i,j)->setScoreTarget(false);
		}
	}
}

void GameBoard::updateTokens() {
	if (leftpressed) {
		if (!_midasMode) {
			_tokenSet[3].advanceLeft(_currentTick);
		} else {
			midasLeft();
		}
	}
	if (rightpressed) {
		if (!_midasMode) {
			_tokenSet[3].advanceRight(_currentTick);
		} else {
			midasRight();
		}
	}

	for (int i = 0; i < 4; i++) {
		_tokenSet[i].update(_currentTick);
	}

	if ( _tokenSet[3].AllInvisible()) {
		advanceToken();
	}
}

void GameBoard::midasLeft() {
	GamePiece * leftPieces = new GamePiece[_ry];

	for (int j = 0; j <_ry; j++) {
		leftPieces[j] = GamePiece(*getPieceAt(0, j));
	}

	for (int i = 0; i < _rx; i++) {
		for (int j = 0; j < _ry; j++) {
			if (i == _rx-1) {
				getPieceAt(i,j)->copyPieceState(&leftPieces[j]);
			} else {
				getPieceAt(i,j)->copyPieceState(getPieceAt(i+1,j));
			}
		}
	}
}

void GameBoard::midasRight() {
	GamePiece * rightPieces = new GamePiece[_ry];

	for (int j = 0; j <_ry; j++) {
		rightPieces[j] = GamePiece(*getPieceAt(_rx - 1, j));
	}


	for (int i = _rx-1; i >= 0; i--) {
		for (int j = 0; j < _ry; j++) {
			if (i == 0) {
				getPieceAt(i,j)->copyPieceState(&rightPieces[j]);
			} else {
				getPieceAt(i,j)->copyPieceState(getPieceAt(i-1,j));
			}
		}
	}
}

unsigned int GameBoard::getCurrentGameTime() {
	return (unsigned int)( _advanceScanner ? ((_currentTick - _gameTime) / 1000) : (unsigned int)(_pauseTime/1000) );
}

void GameBoard::updateHud() {
	std::string name = "";
	std::string val = "";
	char temp[10];

	name = "hiscore_val";
	::sprintf(temp,"%d",getHigh());
	val = temp;
	_hud->setValue(name,val);


	name = "time_val";
	::sprintf(temp,"%d",getCurrentGameTime());
	val = temp;
	_hud->setValue(name,val);

	name = "score_val";
	::sprintf(temp,"%d",_score);
	val = temp;
	_hud->setValue(name, val);

	name = "count_val";
	::sprintf(temp,"%d",_totalBlockCount + _blockCount);
	val = temp;
	_hud->setValue(name, val);

	//only leave announcement up for a second
	if (!_advanceScanner) {
		_hud->setValue("announce","Press 'Return' to Start");
	} else if (_currentTick - _announceTime > 1000) {
		_hud->setValue("announce"," ");
	}
}


void GameBoard::checkHighScore() {
	if (!_scoreChecked) {

		_hiScoreTable->addScore(_score);

		if (_score > _high) {
			_high = _score;
			updateHud();			
		}
		_scoreChecked = true;
	}
}

void GameBoard::updateContents() {
	
}

void GameBoard::update(unsigned int currTick) {

	_currentTick = currTick;

	if ( isGameOver() ){
		if (! _scoreChecked) {
			_fg->setDisplayInfo("Press 'BackSpace' to Return to Mode Selection.  Press 'Return' to Start");
		}
		checkHighScore();
		return;
	}

	if (_isThemeChanging) {
		if(_fg->isComplete()) {
			_fg->setFade(FADE_IN);
			_fg->start();
			applyNextTheme();
			_isThemeChanging = false;
		}
	}

	if (_audioManager->hasBeat(_currentTick)) {
		_icon->Pulse();
	}

	if (_advanceScanner) {
		updateTokens();
		_scanner->update(_currentTick);
		for (int i = 0; i < _rx; i++)
		{
			for (int j = (_ry - 1) ; j >= 0; j--)
			{
				getPieceAt(i,j)->update(_currentTick);
			}
		}
	}


	markScoreTargets();

	int currentColumn = _scanner->getCurrentColumn();

	dropPieces();

	int targetCount = scanTo(currentColumn);

	//unfortunate but true - we need to run this again
	markScoreTargets();

	if (targetCount == 0) {
		cleanScanned(currentColumn);
	} else {
		_canBonus = _blockCount > 0;
	}

	if (_scanner->isReset()) {
		//clean the scanned blocks including the last column
		cleanScanned(_rx-1);

		_totalBlockCount += _blockCount;

		int blockScore = _blockCount * 40;
		if (_blockCount > 3) {
			blockScore *= _blockCount;
		}
		addToScore(blockScore);
		resetScan();
		resetContents();
		_blockCount = 0;
	}
	
	_grid->update(currTick);
	
	updateContents();

	updateHud();
}
void GameBoard::changeTheme() {
	_fg->setFade(FADE_OUT);
	_fg->start();
	_isThemeChanging = true;
}

void GameBoard::dump()
{
	FILE *fp = fopen("PieceDump.csv","w");
	if (fp)
	{
		fseek(fp,0,SEEK_SET);
		fprintf(fp,"Column, Row, Color, Y, X, Dim, InMotion, Magic, Overlap, Scanned, Visible, FallTo\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			for (int i = 0 ; i < _rx ; i++)
			{
				fprintf(fp,"%d, %d, %d, %f, %f, %f, %s, %s, %s, %s, %s, %f\n",i,j,getPieceAt(i,j)->getColor(),getPieceAt(i,j)->getY(),getPieceAt(i,j)->getX(),getPieceAt(i,j)->getDimension(),(getPieceAt(i,j)->isStopped()?"true":"false"),(getPieceAt(i,j)->isScoreTarget()?"true":"false"),(getPieceAt(i,j)->isOverlap()?"true":"false"),(getPieceAt(i,j)->isScanned()?"true":"false"),(getPieceAt(i,j)->isRenderable()?"true":"false"),getPieceAt(i,j)->getScreenMinY());
				//to standard out as well
			}
		}
		fclose(fp);

		printf("--------------------------------------------------------\n");
		printf("visible\n");
		printf("--------------------------------------------------------\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			printf("%d\t",j);
			for (int i = 0 ; i < _rx ; i++)
			{
				printf("|%s",getPieceAt(i,j)->isRenderable() ? ( getPieceAt(i,j)->getColor() == 0 ? "Y" : "X") : " ");
			}
			printf("|\n");
		}

		
		printf("--------------------------------------------------------\n");
		printf("connected\n");
		printf("--------------------------------------------------------\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			printf("%d\t",j);
			for (int i = 0 ; i < _rx ; i++)
			{
				printf("|%s",getPieceAt(i,j)->isRenderable() ? ( getPieceAt(i,j)->isConnected() ? "X" : " ") : " ");
			}
			printf("|\n");
		}


		printf("--------------------------------------------------------\n");
		printf("stopped\n");
		printf("--------------------------------------------------------\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			printf("%d\t",j);
			for (int i = 0 ; i < _rx ; i++)
			{
				printf("|%s",getPieceAt(i,j)->isRenderable() ? ( getPieceAt(i,j)->isStopped() == 0 ? "X" : " ") : " ");
			}
			printf("|\n");
		}

		printf("--------------------------------------------------------\n");
		printf("scanned\n");
		printf("--------------------------------------------------------\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			for (int i = 0 ; i < _rx ; i++)
			{
				printf("|%s",getPieceAt(i,j)->isScanned() ? ( getPieceAt(i,j)->getColor() == 0 ? "X" : "O") : " ");
			}
			printf("|\n");
		}

		printf("--------------------------------------------------------\n");
		printf("score target\n");
		printf("--------------------------------------------------------\n");
		for (int j = (_ry - 1) ; j >= 0; j-- )
		{
			for (int i = 0 ; i < _rx ; i++)
			{
				printf("|%s",getPieceAt(i,j)->isScoreTarget() ? ( getPieceAt(i,j)->getColor() == 0 ? "X" : "O") : " ");
			}
			printf("|\n");
		}

	}
}


/* Rotate the token
 * dir - rotation direction
 * 0 - Clockwise;
 * 1 - CounterClockWise
 */
void GameBoard::rotateToken( Rotation dir) {
	_tokenSet[3].rotate(dir) ;
}

void GameBoard::advanceToken() {
	_tokenCount++;
	for (int tokenPos = 3; tokenPos >0; tokenPos--) {
		if (tokenPos == 3) {
			int halfway =  _rx / 2;
			float leftMostX = halfway * _dim + getMinX() - _dim;
			float bottomMostY = getMaxY();
			float y0 = bottomMostY;
			float x0 = leftMostX;
			_tokenSet[tokenPos].init(x0,y0,_dim);
		}
		_tokenSet[tokenPos].copyColors( _tokenSet[tokenPos - 1] );

	}
	//every 36th token is a special
	_tokenSet[0].assignNewColors( ( ( _tokenCount + 1) % 36 == 0) );
}

void GameBoard::updateSpecialAt(int x, int y) {
	int x0 = -1;
	int y0 = -1;
	bool canSpecial = false;
	if (x-1 >=0) {
		if (y + 1 < getRowMax() ) {
			Block UL(getPieceAt(x-1,y+1),
					getPieceAt(x,y+1),
					getPieceAt(x-1,y),
					getPieceAt(x,y));
			if ( UL.isScoreTarget() &&  UL.hasSpecial(x0,y0) ) {
				canSpecial = true;
				markSpecial(x -1 + x0, y + 1 - y0);
			}
		}

		x0 = -1;
		y0 = -1;

		if (y-1 >= 0) {
			Block LL(getPieceAt(x-1,y),
					getPieceAt(x,y),
					getPieceAt(x-1,y-1),
					getPieceAt(x,y-1));
			if ( LL.isScoreTarget() &&  LL.hasSpecial(x0,y0) ) {
				canSpecial = true;
				markSpecial(x -1 +x0 , y - y0);
			}
		}
	}

	x0 = -1;
	y0 = -1;

	if (x + 1 < getColMax()) {
		if (y + 1 < getRowMax() ) {
			Block UR(getPieceAt(x,y+1),
					getPieceAt(x+1,y+1),
					getPieceAt(x,y),
					getPieceAt(x+1,y));
			if ( UR.isScoreTarget() &&  UR.hasSpecial(x0,y0) ) {
				canSpecial = true;
				markSpecial(x + x0, y + 1 - y0);
			}
		}

		x0 = -1;
		y0 = -1;

		if (y-1 >= 0) {
			Block LR(getPieceAt(x,y),
					getPieceAt(x+1,y),
					getPieceAt(x,y-1),
					getPieceAt(x+1,y-1));
			if ( LR.isScoreTarget() &&  LR.hasSpecial(x0,y0) ) {
				canSpecial = true;
				markSpecial(x +x0 , y - y0);
			}
		}
	}
	
	if (canSpecial) {
		_audioManager->playSoundEffect(AUDIO_SPECIAL);
	}
}

