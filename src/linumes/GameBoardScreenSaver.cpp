#include "GameBoardScreenSaver.h"
#include "Block.h"

GameBoardScreenSaver::GameBoardScreenSaver( float dim, int rx, int ry) : GameBoard(dim,rx,ry) {
}

GameBoardScreenSaver::~GameBoardScreenSaver()
{	
	
}

void GameBoardScreenSaver::init() {
	if (currTheme == NULL)
	{
		currTheme = themeManager->getCurrentTheme();
	}
	
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

	_grid->setTheme(currTheme);
	_scanner->setTheme(currTheme);
	_bg->setTheme(currTheme);
}

int GameBoardScreenSaver::scanTo(int column) {
	int targetCount = 0;
	if (column < _rx) {
	  for (int j = _ry - 1; j >= 0; j--)
		{
		  
			if (getPieceAt(column,j)->isScoreTarget()) {
				getPieceAt(column,j)->setScanned(  true);
				targetCount++;
			}
		}
	}
	return targetCount;	
}

void GameBoardScreenSaver::toggleVisible() {
	for (int i = 0 ; i < _rx; i++) {
		for (int j = 0; j < _ry; j++) {
			getPieceAt(i,j)->setRenderable(!getPieceAt(i,j)->isRenderable());
		}
	}
}


void GameBoardScreenSaver::markScoreTargets() {
for (int i = 0; i < _rx-1; i++)
  {
    for (int j = 1; j < _ry ; j++)
    {     	   	
    	Block block( getPieceAt(i,j),
    							 getPieceAt(i+1,j),
    							 getPieceAt(i,j-1),
    							 getPieceAt(i+1,j-1));
    							 
    	if (block.isScoreTarget()) {
    							 getPieceAt(i,j)->setScoreTarget(true);
    							 getPieceAt(i+1,j)->setScoreTarget(true);
    							 getPieceAt(i,j-1)->setScoreTarget(true);
    							 getPieceAt(i+1,j-1)->setScoreTarget(true);
    	}
    }
  }	
}

void GameBoardScreenSaver::resetScan() {
	for (int i = 0; i < _rx; i++)
  {
    for (int j = (_ry - 1) ; j >= 0; j--)
    {    	
      getPieceAt(i,j)->setScanned( false);
    }
  }	
}
/*
void GameBoardScreenSaver::cleanScanned(int column) {
    //don't erase all the Sets on the board
    if ((column < _rx) && (lastscanned < _rx)) { 
	    for (int i = lastscanned; i <= column ; i++)
	    {
	      for (int j = _ry - 1; j >= 0; j--)
	      {      
	        if ( ( getPieceAt(i,j)->isScanned() ) && (! getPieceAt(i,j)->isStopped() ) )
	        {
	          getPieceAt(i,j)->setRenderable(false);
					  getPieceAt(i,j)->setScanned( false );
					  getPieceAt(i,j)->setConnected( false );
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
						getPieceAt(i,j)->setConnected(false);
					}
				}
	    }
    }
}
*/
void GameBoardScreenSaver::update(unsigned int currTime) {
	_currentTick = currTime;
	bool allVisible = true;
	if (_advanceScanner) {
		_scanner->update(_currentTick);
		for (int i = 0; i < _rx; i++)
		{
			for (int j = (_ry - 1) ; j >= 0; j--)
			{
				getPieceAt(i,j)->update(_currentTick);
				if (! getPieceAt(i,j)->isRenderable()) {
					allVisible = false;
				}
			}
		}
	}	

	int currentColumn = _scanner->getCurrentColumn();

	dropPieces();

	int targetCount = scanTo(currentColumn);
	
	markScoreTargets();
	
	if (targetCount == 0) {		
		cleanScanned(currentColumn);
	}
	
	if (_scanner->isReset()) {		
		//clean the scanned blocks including the last column		
		
		jumbleBlocks();
		cleanScanned(_rx-1);
		resetScan();
	}
	
	if (allVisible) {
		toggleVisible();
	}

}

void GameBoardScreenSaver::jumbleBlocks() {
#ifdef MING_RANDOM
    int numChanges = rand() % (_rx * _ry);
#else
    int numChanges = random() % (_rx * _ry);
#endif    
	
	for (int i = 0; i < numChanges; i++) {
#ifdef MING_RANDOM
		int x1 = rand() % _rx;
		int y1 = rand() % _ry;
#else
		int x1 = random() % _rx;
		int y1 = random() % _ry;
#endif
		getPieceAt(x1,y1)->setNewColor(false);
		getPieceAt(x1,y1)->setRenderable(true);
				
	}
}

void GameBoardScreenSaver::Draw() {
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity( );
	glTranslatef( 0.0f, 0.0f, -10.0f );

	drawBackground();
	drawGrid();
	drawPieces();
	drawScoreTargets();
	drawScanner();
	
	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}

void GameBoardScreenSaver::toggleScanner(unsigned int currTime) {

	_advanceScanner = (!_advanceScanner);

	if (_advanceScanner) {
		_gameTime = _currentTick - _pauseTime;
	} else {
		_pauseTime = _currentTick - _gameTime;
	}
	_scanner->togglePause();
};

