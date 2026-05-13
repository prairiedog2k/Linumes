#include "TimeLimitedGameBoard.h"
#include "framework/ResourceHelper.h"
#include "framework/FontResource.h"
#include "framework/Font.h"
#include "framework/Utils.h"
#include "HUDTextTypes.h"
#include "BaseTextTypes.h"
#include <cstdlib>

#include "HighScoreManager.h"

TimeLimitedGameBoard::TimeLimitedGameBoard() : GameBoard(0.2f,16,10), _gameDuration(60), _timeOver(false),_quad() {
	char buff[20];
	std::snprintf(buff, sizeof(buff), "TimeLimited%03d", _gameDuration);
	_gameName = buff;
}

TimeLimitedGameBoard::TimeLimitedGameBoard(unsigned int gameDuration) : GameBoard(0.2f,16,10), _gameDuration(gameDuration), _timeOver(false), _quad()
{
	char buff[20];
	std::snprintf(buff, sizeof(buff), "TimeLimited%03d", _gameDuration);
	_gameName = buff;
}

TimeLimitedGameBoard::~TimeLimitedGameBoard()
{
}

void TimeLimitedGameBoard::updateHud() {
	_hud->setValue("hiscore_val", std::to_string(getHigh()));
	_hud->setValue("time_val",    std::to_string(_gameDuration - getCurrentGameTime()));
	_hud->overrideText("score_txt", "Block");
	_hud->setValue("score_val",   std::to_string(_blockCount));
	_hud->overrideText("count_txt", "Total");
	_hud->setValue("count_val",   std::to_string(_totalBlockCount + _blockCount));

	//only leave announcement up for a second
	if (!_advanceScanner) {
		_hud->setValue("announce","Press 'Return' to Start");
	} else if (_currentTick - _announceTime > 1000) {
		_hud->setValue("announce"," ");
	}
}


void TimeLimitedGameBoard::drawContents() {
	GameBoard::drawContents();
	if ( isGameOver() ) {
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		glBindTexture( GL_TEXTURE_2D, ResourceHelper::getTextureResource(getTheme(),  "hi_score_table" )->getResource());

		glTranslatef( 0.0,0.0, -5.0f );
				
		_quad.setDimensionAndPosition2D(0.0,0.0,2.0f);
		_quad.setZ(1.0f);
		_quad.Draw();
		
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		if (_timeOver) {
			Font *f1 = ResourceHelper::getFontResource(getTheme(),  HUD_FONT )->getResource();
			f1->drawText(std::string("Game Over").c_str(), xformX(512), xformY(690), true);
			
			std::string highs = _hiScoreTable->getTableString();
			Font *f3=ResourceHelper::getFontResource(getTheme(),  BASE_FONT_24 )->getResource();
			f3->drawText(highs.c_str(),xformX(400), xformY(600), true, true);

			std::string score = "[Block Count x " + std::to_string(_totalBlockCount) + "]";
			Font *f2 = ResourceHelper::getFontResource(getTheme(),  HUD_FONT )->getResource();
			f2->drawText(score.c_str(), xformX(512), xformY(20), true);
		} else {
			Font *f1 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_72 )->getResource();
			f1->setRGB(1.0,0.0,0.0);
			f1->drawText(std::string("Fail!").c_str(), xformX(512), xformY(384), true);						
		}
	}
	
}
void TimeLimitedGameBoard::reset() {
	GameBoard::reset();
	_timeOver = false; 
}

void TimeLimitedGameBoard::checkHighScore() {
	if (!_scoreChecked && _timeOver) {
		
		_hiScoreTable->addScore(_totalBlockCount);
		if (_totalBlockCount > _high) {
			_high = _totalBlockCount;
		}
		_scoreChecked = true;
	}
}
void TimeLimitedGameBoard::update(unsigned int currTick) {
	_currentTick = currTick;
	if ( (getCurrentGameTime() ) == (_gameDuration) ) {
		_fg->setFade(FADE_OUT);
		_fg->start();
		_totalBlockCount += _blockCount;
		_blockCount = 0;
		_timeOver = true;
		updateHud();
		setGameOver(true);		
		
	}
	GameBoard::update(currTick);
}
