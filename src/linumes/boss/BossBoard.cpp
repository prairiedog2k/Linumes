#include "BossBoard.h"
#include "framework/TextureQuad.h"
#include "framework/ResourceHelper.h"
#include "framework/Utils.h"

#include <math.h>

#include "linumes/HighScoreManager.h"
#include "linumes/BaseTextTypes.h"


BossBoard::BossBoard() : 
    GameBoard(0.2f,16,10), 
    _boss("jublo.xml"),
    _bossIcon( new BossIcon() ),
    _bossAttacks(0),
    _attackStart(0),
    _attackDuration(250),
    _bossWinPlayed(false)
{
	
	_bossPieces = new BossPiece[16 * 10];
	_bossIcon->setRenderable(true);
	_gameName = "jublo";	
}

BossBoard::~BossBoard() {
	if (_bossPieces != NULL)
	{
		delete[] _bossPieces;
	}
}

void BossBoard::assignInitialTheme() {
	if (currTheme == NULL)
	{
		if ( _boss.getPreferredTheme().length() > 0) {
			currTheme = themeManager->getNamedTheme( _boss.getPreferredTheme() );
		} else {
			currTheme = themeManager->getCurrentTheme();
		}
	}
}

void BossBoard::init() {
    _boss.load();
#ifdef DEBUG
    _boss.dump();
#endif    
    GameBoard::init();
    
	_bossIcon->setDimension(3 * _dim);
	_bossIcon->setX(getMaxX() + 0.1 * _dim);
	_bossIcon->setY(getMinY() - 2.90 * _dim);
	_bossIcon->setBossTexture( _boss.getIconTexture());
	_bossIcon->setBossMask (_boss.getIconMask());
	
    for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{
            BossPiece *piece = dynamic_cast<BossPiece *>( getPieceAt(i,j) );
            if (_boss.isBossBlock(i,j) ) {
                piece->setBoss(true);
                piece->setRenderable(true);
                piece->setColor( _boss.getPatternColor(i,j) );
                piece->setBossTexture( _boss.getTexture(i,j) );
            } else {
                piece->setBoss(false);
            }
        }
    }
}

void BossBoard::reset() {
	_boss.reset();
	GameBoard::reset();
	
    for (int i = 0; i < _rx; i++)
	{
		for (int j = (_ry - 1) ; j >= 0; j--)
		{
            BossPiece *piece = dynamic_cast<BossPiece *>( getPieceAt(i,j) );
            _boss.resetAt(i,j);
            if (_boss.isBossBlock(i,j) ) {            	
                piece->setBoss(true);
                piece->setRenderable(true);
                piece->setColor( _boss.getPatternColor(i,j) );
                piece->setBossTexture( _boss.getTexture(i,j) );
            } else {
                piece->setBoss(false);
            }
        }
    }
	_bossWinPlayed = false;
}

GamePiece *BossBoard::getPieceAt(int x, int y) {
	int pos =(  x * _ry ) + y;
	return 	&_bossPieces[pos];
}

void BossBoard::dropPieces() {
	for (int i = 0; i < _rx; i++) {
		for (int j = _ry - 1 ;  j > 0; j--) {
			//for (int j = 1 ;  j  < _ry; j++) {
			if ( !getPieceAt(i,j-1)->isRenderable() &&
					getPieceAt(i,j-1)->isStopped() &&
					getPieceAt(i,j  )->isRenderable() &&
				  ! (dynamic_cast<BossPiece *>(getPieceAt(i,j) ) )->isBoss() )  {

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

void BossBoard::cleanScanned(int column) {
	//don't erase all the Sets on the board
	if ((column < _rx) && (lastscanned < _rx)) {
		for (int i = lastscanned; i <= column ; i++)
		{
			for (int j = _ry - 1; j >= 0; j--)
			{
				if ( getPieceAt(i,j)->isScanned() )
				{
					if ( _boss.attackAt(i,j) ) {
						_audioManager->playAudioResource(_boss.getDamageAudio());
						//for every hitpoint removed perform a one-time 
						//downgrade of the bosses attack by 4 blocks;
						_boss.adjustAttack(4);
						_bossAttacks++;
					}
					dynamic_cast<BossPiece *>(getPieceAt(i,j))->setBoss(false);
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

void BossBoard::evaluateBonus() {
	if (_bossAttacks > 0 ) {
		_audioManager->playAudioResource(_boss.getDamageAudio());
		_announceTime = _currentTick;
		char temp[20];
		sprintf(temp,"Boss Attack %d X 10K",_bossAttacks);
		_hud->setValue("announce",temp);			
		addToScore(10000 * _bossAttacks);
		_bossAttacks = 0;
	} 
}

void BossBoard::addToBlockCount (int count) {
	GameBoard::addToBlockCount(count);
	_boss.adjustAttack(count);
	_bossIcon->Pulse();
}

void BossBoard::updateHud() {
	std::string name = "";
	std::string val = "";
	char temp[10];

	name = "hiscore_txt";
	val = "Score";
	_hud->overrideText(name,val);

	name = "hiscore_val";
	::sprintf(temp,"%d",_score);
	val = temp;
	_hud->setValue(name,val);

	name = "time_txt";
	val = "Attack In";
	_hud->overrideText(name,val);

	
	name = "time_val";
	if (_boss.getNextAttackTurn() > 1) {
		::sprintf(temp,"%d Passes", _boss.getNextAttackTurn() );
	} else {
		::sprintf(temp,"%d Pass", _boss.getNextAttackTurn() );
	}
	val = temp;
	_hud->setValue(name,val);

	name = "score_txt";
	val = "Attack";
	_hud->overrideText(name,val);

	name = "score_val";
	::sprintf(temp,"%d",_boss.getCurrentAttack());
	val = temp;
	_hud->setValue(name,val);


	name = "count_txt";
	val = "Boss HP";
    _hud->overrideText(name, val);
    
    
	name = "count_val";
	::sprintf(temp,"%d",_boss.getHitPoints());
	val = temp;
	_hud->setValue(name, val);

	//only leave announcement up for a second
	if (!_advanceScanner) {
		_hud->setValue("announce","Press 'Return' to Start");
	} else if (_currentTick - _announceTime > 1000) {
		_hud->setValue("announce"," ");
	}

}

void BossBoard::resetContents() {
	if (_advanceScanner) {
		_boss.addTurn();		
		if (_boss.canAttack()) {
			_audioManager->playAudioResource(_boss.getAttackAudio());
			//rain hell!!!
			for (int i = 0; i < _boss.getCurrentAttack(); i++) {
				int pos = 0;
#ifdef MING_RANDOM
				pos = rand() % 160;
#else
				pos = random() % 160;
#endif
				int y = pos / 16;
				int x = pos % 16;

				if  ((!dynamic_cast<BossPiece *>(getPieceAt(x,y))->isBoss()) && (! getPieceAt(x,y)->isRenderable() ) ) {
					getPieceAt(x,y)->setNewColor(false);
					getPieceAt(x,y)->setRenderable(true);
				}
			}
			_attackStart = _currentTick;
			_boss.resetAttack();
			
		}
	}
}

void BossBoard::drawGameOver() {
	if ( isGameOver() ) {
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		glBindTexture( GL_TEXTURE_2D, ResourceHelper::getTextureResource(getTheme(),  "hi_score_table" )->getResource());

		glTranslatef( 0.0,0.0, -5.0f );
		TextureQuad _quad;		
		_quad.setDimensionAndPosition2D(0.0,0.0,2.0f);
		_quad.setZ(1.0f);
		_quad.Draw();
		
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		if (_boss.isDead()) {
			Font *f1 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_48 )->getResource();
			f1->setRGB(0.0,1.0,0.0);
			std::string win = "You Beat ";
			f1->drawText(win.c_str(), xformX(512), xformY(690), true);
			win = _boss.getName();
			f1->drawText(win.c_str(), xformX(512), xformY(630), true);
			
			
			char highs[300];
			::sprintf( highs,"%s",_hiScoreTable->getTableString().c_str() );
			Font *f3=ResourceHelper::getFontResource(getTheme(),  BASE_FONT_24 )->getResource();
			f3->drawText(highs,xformX(400), xformY(600), true, true);
			 
			char score[64];
			::sprintf(score,"[Score %d]", _score );
			Font *f2 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_48 )->getResource();
			f2->drawText(score, xformX(512), xformY(20), true);
		} else {
			Font *f1 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_72 )->getResource();
			f1->setRGB(1.0,0.0,0.0);
			std::string fail = "Failed...";
			f1->drawText(fail.c_str(), xformX(512), xformY(425),true);
			fail =_boss.getName();
			f1->drawText(fail.c_str(), xformX(512), xformY(350),true);
			fail = " Wins!!!";
			f1->drawText(fail.c_str(), xformX(512), xformY(275),true);
									
		}
	}	
}

void BossBoard::drawAttack() {
	if ( isAttacking() ) {
		float percentAttack = (float)( _currentTick -_attackStart) / (float)(_attackDuration);
		float critDim = ( percentAttack - 0.5f ) * 2.0f;
		critDim *= critDim;
		critDim = ::sqrt(critDim);			
		critDim = _dim + (critDim * _dim);
		float dd = 1.25f * critDim;
		TextureQuad _quad;
		
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		
		glColor3f(1.0f,1.0f,1.0f);
		
		glRotatef(45.0f * percentAttack, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
			glTranslatef( (GLfloat)- 2.0f * dd, (GLfloat) -2.0f * dd, -3.0f );
			_quad.setZ(1.0f);
			_quad.setDimensionAndPosition2D(2.0f * dd, 2.0f * dd, 4.0f * dd );
			
			glBindTexture( GL_TEXTURE_2D, _boss.getBGMask() );
			glBlendFunc(GL_DST_COLOR,GL_ZERO);		
			_quad.Draw();
			
			glBindTexture( GL_TEXTURE_2D, _boss.getBGTexture() );
			glBlendFunc(GL_ONE, GL_ONE);
			_quad.Draw();
		glPopMatrix();
		
		glLoadIdentity();
		glPushMatrix();
			glTranslatef( (GLfloat)- 2.0f * critDim, (GLfloat) -2.0f * critDim, -3.0f );
			_quad.setZ(1.0f);
			_quad.setDimensionAndPosition2D(2.0f * critDim, 2.0f * critDim, 4.0f * critDim );
			
			glBindTexture( GL_TEXTURE_2D, _boss.getFGMask() );
			glBlendFunc(GL_DST_COLOR,GL_ZERO);		
			_quad.Draw();
			
			glBindTexture( GL_TEXTURE_2D, _boss.getFGTexture() );
			glBlendFunc(GL_ONE, GL_ONE);
			_quad.Draw();
		glPopMatrix();
		
		
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}

void BossBoard::drawContents() {
	GameBoard::drawContents();
	_bossIcon->Draw();
	drawGameOver();
	drawAttack();
}

void BossBoard::updateContents() {
	if (isGameOver() && !_bossWinPlayed) {
		_audioManager->playAudioResource(_boss.getWinAudio());
		_bossWinPlayed = true;
	}
	if (_boss.isDead()) {
		if ( ! isGameOver()) {
			_audioManager->playAudioResource(_boss.getDieAudio());
			_bossWinPlayed = true;
			setGameOver(true);
		}
	}
}
