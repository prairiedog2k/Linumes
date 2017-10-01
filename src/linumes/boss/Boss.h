#ifndef BOSS_H_
#define BOSS_H_

#include <string>
#include <vector>
#include "framework/TextureResource.h"
#include "framework/AudioResource.h"
#include "GL/gl.h"

#include "BossPiece.h"

class Boss
{
private:
	std::string _bossFile;
	std::string _name;
	std::string _dir;
	std::string _preferredTheme;
	int _turnsToAttack;
	int _currentTurn;
	int _turnAttack;
	int _cumulativeBlocks;
	int _attackReduce;
	int _hitPoints;
	int _currentHitPoints;
	
	TextureResource *_color0;
	TextureResource *_color1;
	TextureResource *_bg;
	TextureResource *_fg;
	TextureResource *_bgMask;
	TextureResource *_fgMask;
	TextureResource *_icon;
	TextureResource *_iconMask;
	
	AudioResource *_attack;
	AudioResource *_damage;
	AudioResource *_die;
	AudioResource *_win;
	
    bool _shape[ 16 * 10 ];
    bool _currentShape[ 16 * 10];
	int _pattern[4];

	void tokenize(const std::string& str,
	                    std::vector<std::string>& tokens,
	                    const std::string& delimiters = ",");
public:
	Boss(std::string bossFile);
	virtual ~Boss();
	
	
	//loads boss data from a file
	void load();
	//return the color of the block according to the shape and the pattern, -1 if not a boss block
    int getPatternColor(int x, int y);
	// return whether an attack at x,y was a success	
	bool attackAt(int x, int y);
	void resetAt(int x, int y) { _currentShape[(y * 16) + x] = _shape[ (y * 16) + x]; };
	//return the texture for the specified coord 0 if not a boss block
	GLuint getTexture(int x, int y);
	//return the background texture
	GLuint getBGTexture();
	//return the foreground texture
	GLuint getFGTexture();
	//return the Icon texture
	GLuint getIconTexture();
	//return the background mask
	GLuint getBGMask();
	//return the foreground mask
	GLuint getFGMask();
	//return the Icon mask
	GLuint getIconMask();

	AudioResource *getAttackAudio() { return _attack;};
	AudioResource *getDamageAudio() { return _damage;};
	AudioResource *getDieAudio() { return _die;}; 
	AudioResource *getWinAudio() { return _win;};	
	
	//dump
	void dump();

	//inlines
	//return the strength of the attacj in new blocks to add to the game board
	int getCurrentAttack() { return _turnAttack - (_cumulativeBlocks / _attackReduce) > 0 ? _turnAttack - (_cumulativeBlocks / _attackReduce) : 0 ; };
	//return whether or not the block in question is a boss block 
	bool isBossBlock(int x, int y) { return _currentShape[ (16 * y) + x]; };
	//is the boss dead?
	bool isDead() { return _currentHitPoints <= 0; };
	//return the number of hit points the boss has
	int getHitPoints() { return _currentHitPoints; };
	//each scanner pass add a turn
	void addTurn() { _currentTurn++; };
	//each scanner pass reduce the boss attack by the number of blocks created
	//divided by the attack reduction weight
	void adjustAttack(int blocks) { _cumulativeBlocks += blocks; };
	//determines whether the Boss can attack 
	bool canAttack() { return 0 == (_currentTurn) % _turnsToAttack; };	
	int getNextAttackTurn() { return _turnsToAttack - (_currentTurn  % _turnsToAttack); };
	//after the boss attacks reset his attack power
	void resetAttack() { _cumulativeBlocks = 0; };
	
	void reset();
	std::string getPreferredTheme() { return _preferredTheme; };
	std::string getName() { return _name; };
    	 
};

#endif /*BOSS_H_*/
