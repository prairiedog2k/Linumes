#include "Boss.h"

#include <iostream>
#include "xmlParser.h"
#include "framework/FileUtils.h"

#include "BossModeTypes.h"

#include "framework/XMLUtils.h"
#include "framework/XMLThemeTypes.h"

Boss::Boss(std::string bossFile) : _bossFile(bossFile), 
	_name(),
	_dir(),
	_preferredTheme(),
	_turnsToAttack(0),
	_currentTurn(0),
	_turnAttack(0),
	_cumulativeBlocks(0),
	_attackReduce(0),
	_hitPoints(0),
	_currentHitPoints(0),
    _color0(NULL),
    _color1(NULL), 
    _bg(NULL),
    _fg(NULL),
    _bgMask(NULL),
    _fgMask(NULL),
    _icon(NULL),
    _iconMask(NULL),
    _attack(NULL),
    _damage(NULL),
    _die(NULL),
    _win(NULL) {
	for (int i = 0; i < (16 * 10); i++) {
		_shape[i] = false;
		_currentShape[i]= false;
	}
    for (int i = 0; i < 4; i++) {
        _pattern[i] = -1;
    }	
}

Boss::~Boss()
{
    if (NULL != _color0 ) {
    	_color0->release();
        delete _color0;
        _color0 = NULL;
    }
    
    if (NULL != _color1) {
    	_color1->release();    	
        delete _color1;
        _color1 = NULL;
    }

    if (NULL != _bg) {
    	_bg->release();    	
        delete _bg;
        _bg = NULL;
    }

    if (NULL != _fg) {
    	_fg->release();    	
        delete _fg;
        _fg = NULL;
    }

    if (NULL != _icon) {
    	_icon->release();    	
        delete _icon;
        _icon = NULL;
    }
    
    if (NULL != _bgMask) {
    	_bgMask->release();    	
        delete _bgMask;
        _bgMask = NULL;
    }

    if (NULL != _fgMask) {
    	_fgMask->release();    	
        delete _fgMask;
        _fgMask = NULL;
    }

    if (NULL != _iconMask) {
    	_iconMask->release();    	
        delete _iconMask;
        _iconMask = NULL;
    }
    
    if (NULL != _attack) {
    	_attack->release();    	
        delete _attack;
        _attack = NULL;
    }
    if (NULL != _damage) {
    	_damage->release();    	
        delete _damage;
        _damage = NULL;
    }
    if (NULL != _die) {
    	_die->release();    	
        delete _die;
        _die = NULL;
    }
    if (NULL != _win) {
    	_win->release();    	
        delete _win;
        _win = NULL;
    }

}

void Boss::reset() {
	_currentTurn = 0;
	_cumulativeBlocks = 0;
	_currentHitPoints = _hitPoints;
}

bool Boss::attackAt(int x, int y) {
	if (!isBossBlock(x,y)) {
		return false;
	}
	_currentShape[ (16 * y) + x] = false; 
	_currentHitPoints--; 
	return true;
}


void Boss::tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

int Boss::getPatternColor(int x, int y) {
    if ( !isBossBlock(x,y) ) {
        return -1;
    }
    int ipos = x % 2;
    int jpos = y % 2;
    int retVal =  _pattern[jpos * 2 + ipos];
    return retVal;
}

void Boss::load() {
	if (fileExists(_bossFile)) {
		XMLNode xMainNode=XMLNode::openFileHelper(_bossFile.c_str(),BOSS_ROOT);
		if (! xMainNode.isEmpty() ) {
			_name = nodeAttributeAsString( xMainNode, BOSS_ATTR_NAME);
			_dir = nodeAttributeAsString( xMainNode, BOSS_ATTR_DIR);
			std::string tmp;
			tmp = nodeAttributeAsString( xMainNode,BOSS_ATTACK_TURN);
			_turnsToAttack = ::atoi(tmp.c_str());
			tmp = nodeAttributeAsString( xMainNode,BOSS_ATTACK_DAMAGE);
			_turnAttack = ::atoi(tmp.c_str());
			tmp = nodeAttributeAsString( xMainNode, BOSS_ATTACK_REDUCE);
			_attackReduce = ::atoi(tmp.c_str());			
			int pos = 0;
			//get Preferred Theme For Boss 
			XMLNode themeNode = xMainNode.getChildNode(BOSS_THEME);
			if (! themeNode.isEmpty() )  {
				_preferredTheme = themeNode.getText();
			}
	        //get media for boss
	        XMLNode mediaNode = xMainNode.getChildNode(BOSS_MEDIA);
	        if ( !mediaNode.isEmpty() ) {
	            int i = 0;
	            XMLNode resourceNode;
	            std::string target;
	            do {
	                resourceNode = mediaNode.getChildNode(THEME_RESOURCE, &i);
	                if ( ! resourceNode.isEmpty() ) {
	                    target = nodeAttributeAsString( resourceNode, THEME_ATTR_NAME);
	                    if (target.compare(BOSS_COLOR0) == 0 ) {
	                        _color0 = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));    
	                    }
	                    if (target.compare(BOSS_COLOR1) == 0) {
	                        _color1 = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ATT_BG) == 0) {
	                    	_bg = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ATT_FG) == 0) {
	                    	_fg = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ICON) == 0) {
	                    	_icon = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ATT_BG_MASK) == 0) {
	                    	_bgMask = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ATT_FG_MASK) == 0) {
	                    	_fgMask = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_ICON_MASK) == 0) {
	                    	_iconMask = dynamic_cast<TextureResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_AUDIO_ATTACK) == 0) {
	                    	_attack = dynamic_cast<AudioResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_AUDIO_DAMAGE) == 0) {
	                    	_damage = dynamic_cast<AudioResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_AUDIO_DIE) == 0) {
	                    	_die = dynamic_cast<AudioResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                    if (target.compare(BOSS_AUDIO_WIN) == 0) {
	                    	_win = dynamic_cast<AudioResource *>(createResourceFromNode(resourceNode, _dir));
	                    }
	                }
	            }  while (! resourceNode.isEmpty() );
	        }
	        
	        //get shape	of boss		
	        pos = 0;
			XMLNode shapeNode = xMainNode.getChildNode(BOSS_SHAPE);
			if (! shapeNode.isEmpty()) {
				XMLNode rowNode;
				int row = 0;
				int count = 9;
				do { 
					 rowNode = shapeNode.getChildNode(BOSS_SHAPE_ROW, &row);
					 if (! rowNode.isEmpty()) {						 
						std::string strRow = rowNode.getText();
						std::vector<std::string> tokens;
						tokenize(strRow,tokens);
						int col = 0;
						for (std::vector<std::string>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
							bool isHP = ( (*iter).compare("0") == 0);
							_shape[ (count * 16) + col] = isHP;
							_currentShape[(count * 16) + col] = _shape[ (count * 16) + col]; 
							if (isHP) {
								_hitPoints++;
							}
							col++;
						}
						count--; 
					 }					 
				} while ( ! rowNode.isEmpty());
			}
			
			_currentHitPoints = _hitPoints;
			
			//get color pattern for boss
			XMLNode patternNode = xMainNode.getChildNode(BOSS_PATTERN, &pos);
			if (! patternNode.isEmpty()) {
				XMLNode rowNode;
				int row = 0;
				int count = 1;
				do {
					 rowNode = patternNode.getChildNode(BOSS_PATTERN_ROW, &row);
					 if (! rowNode.isEmpty()) {
						std::string strRow = rowNode.getText();
						std::vector<std::string> tokens;
						tokenize(strRow,tokens);
						int col = 0;
						for (std::vector<std::string>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
	                        int color = (((*iter).compare("O") == 0 ) ? 0 :  1);
	                        _pattern[count * 2 + col] = color;
							col++;
						}
						count--;
					 }
				} while ( ! rowNode.isEmpty());
			}
		}
	}
}

GLuint Boss::getTexture(int x, int y) {
    int color = getPatternColor(x, y);
    if ( ( color < 0 ) || ( color > 1 ) ) {
        return 0;
    }
    if ( 0 == color) {
        return _color0->getResource();
    } else {
        return _color1->getResource();
    }
}

//return the background texture
GLuint Boss::getBGTexture() {
	if (NULL == _bg) {
		return 0;
	}
	return _bg->getResource();	
}
//return the foreground texture
GLuint Boss::getFGTexture() {
	if (NULL == _fg) {
		return 0;
	}
	return _fg->getResource();
}

//return the icon texture
GLuint Boss::getIconTexture() {
	if (NULL == _icon) {
		return 0;
	}
	return _icon->getResource();
}

//return the background texture
GLuint Boss::getBGMask() {
	if (NULL == _bgMask) {
		return 0;
	}
	return _bgMask->getResource();	
}
//return the foreground texture
GLuint Boss::getFGMask() {
	if (NULL == _fgMask) {
		return 0;
	}
	return _fgMask->getResource();
}

//return the icon texture
GLuint Boss::getIconMask() {
	if (NULL == _iconMask) {
		return 0;
	}
	return _iconMask->getResource();
}

void Boss::dump() {
	std::cout << "Name : " << _name << std::endl;
	std::cout << "Turns To Attack : " << _turnsToAttack << std::endl;
	std::cout << "Attack Damage : " <<  _turnAttack << std::endl;
	std::cout << "Blocks for Attack Reduction " << _attackReduce << std::endl;
	std::cout << "Shape : " << endl;
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 16; j++) {
			std::cout << "|" << (_shape[ (16 * i) + j] ? "X" : "."); 
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "Pattern : " << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j >= 0; j--) {
			std::cout << "|" << _pattern[j * 2 + i];			
		}
		std::cout << "|" << std::endl;
	}
}
