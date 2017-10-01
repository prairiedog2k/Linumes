#include "Block.h"
#include <iostream>
#include "BoardTypes.h"
#include "framework/ResourceHelper.h"
#include "framework/TextureResource.h"

/*
 *   ---------
 *   | 2 | 3 |
 *   ---------
 *   | 0 | 1 |
 *   ---------
 */

Block::Block(): Rendered(false), Themed(), _x(0.0f), _y(0.0f), _dim(1.0f), _whole(false), _quad() {
	for (int i = 0; i < 4; i++) {
		_pieces[i] = new GamePiece();
		_pieces[i]->setNewColor(false);   	  
	}
}

Block::Block(Block &block):Rendered(block._renderable), 
_x(block._x), 
_y(block._y),
_dim(block._dim),
_whole(block._whole),
_quad()
{
	setTheme(block._theme);
	GamePiece *gp;
	for (int i = 0; i < 4; i++) {
		gp  = block.pieceAt(i);
		if (gp != 0) {
			_pieces[i] = new GamePiece();
			_pieces[i]->setPiecePos     ( gp->getX(),gp->getY());
			_pieces[i]->setNextY(gp->getNextY());
			_pieces[i]->setDimension     ( gp->getDimension() );
			_pieces[i]->setColor  ( gp->getColor() );
			_pieces[i]->setSpecial( gp->isSpecial() );
			_pieces[i]->setStopped( gp->isStopped() );      
		}
	}
}

Block::Block( const GamePiece *p1, 
		const GamePiece *p2,
		const GamePiece *p3,
		const  GamePiece *p4) :Rendered(true), Themed(), _quad() {
	_pieces[0] = new GamePiece(*p1);
	_pieces[1] = new GamePiece(*p2);
	_pieces[2] = new GamePiece(*p3);
	_pieces[3] = new GamePiece(*p4);
	_x = _pieces[0]->getX();
	_y = _pieces[0]->getY();
	setDimension(_pieces[0]->getDimension());
	setStopped( _pieces[0]->isStopped() );
	isWhole();                
}

Block::~Block()
{
	for (int i = 0; i < 4; i++) {		
		delete _pieces[i];		
	}
}

//use judiciously
GamePiece *Block::pieceAt(int i) { 
	return _pieces[i];
}

void Block::setX(const float x) {
	_x = x;
	_pieces[0]->setX(x);
	_pieces[1]->setX(x + _dim);
	_pieces[2]->setX(x);
	_pieces[3]->setX(x + _dim);
}

void Block::setY(const float y) {
	_y = y; 
	_pieces[0]->setY(y);
	_pieces[1]->setY(y);
	_pieces[2]->setY(y+_dim);
	_pieces[3]->setY(y+_dim);
}

bool Block::AllVisible() {
	bool bRetVal = true;
	if (!_pieces[0]->isRenderable()) 
		bRetVal = false;
	if (!_pieces[1]->isRenderable())
		bRetVal = false;
	if (!_pieces[2]->isRenderable())
		bRetVal = false;            
	if (!_pieces[3]->isRenderable())    
		bRetVal = false;
	return bRetVal;
}

bool Block::AllInvisible() {
	bool bRetVal = true;
	if (_pieces[0]->isRenderable())
		bRetVal = false;
	if (_pieces[1]->isRenderable())
		bRetVal = false;
	if (_pieces[2]->isRenderable())
		bRetVal = false;
	if (_pieces[3]->isRenderable())
		bRetVal = false;
	return bRetVal;
}


bool Block::isWhole() {
	int y1 = (int)((_pieces[0]->getY() * 1000.0f)+0.4999f)/100;
	int y2 = (int)((_pieces[1]->getY() * 1000.0f)+0.4999f)/100;
	if ( y1 != y2) {
		_whole = false;
	} else {
		_whole = true;
	}    
	return _whole;
}

bool Block::countableMagic() {
	bool bRetVal = false;    
	if ( ( _pieces[0]->getColor() == _pieces[1]->getColor() ) &&
			( _pieces[2]->getColor() == _pieces[3]->getColor() ) &&
			( _pieces[0]->getColor() == _pieces[2]->getColor() ) )
		bRetVal = true;
	return bRetVal;
}

bool Block::isScoreTarget() {
	bool bRetVal = false;    
	if ( isWhole() && AllVisible() ) {
		//All pieces the same color
		if ( ( _pieces[0]->getColor() == _pieces[1]->getColor() ) &&
				( _pieces[2]->getColor() == _pieces[3]->getColor() ) &&
				( _pieces[0]->getColor() == _pieces[2]->getColor() ) )
			bRetVal = AllStopped();

	}
	return bRetVal;
}

void Block::setScreenPosition( float x, float y) {
	_x = x;
	_y = y;    
	_pieces[0]->setPiecePos( _x        , _y        );
	_pieces[0]->setNextY(_y);
	_pieces[1]->setPiecePos( _x + _dim , _y        );
	_pieces[1]->setNextY(_y);
	_pieces[2]->setPiecePos( _x        , _y + _dim );
	_pieces[2]->setNextY(_y + _dim);
	_pieces[3]->setPiecePos( _x + _dim , _y + _dim );
	_pieces[3]->setNextY(_y + _dim);    
}

void Block::setDimension( float dim ) {
	_dim = dim;
	_pieces[0]->setDimension( _dim );
	_pieces[1]->setDimension( _dim );
	_pieces[2]->setDimension( _dim );
	_pieces[3]->setDimension( _dim );
}

void Block::setStopped( bool inmotion) {
	_inmotion = inmotion;
	_pieces[0]->setStopped( _inmotion );
	_pieces[1]->setStopped( _inmotion );
	_pieces[2]->setStopped( _inmotion );
	_pieces[3]->setStopped( _inmotion );    
}



bool Block::InMotion() {
	return _inmotion;
}

bool Block::AllStopped() {
	return ( _pieces[0]->isStopped() &&
			_pieces[1]->isStopped() &&
			_pieces[2]->isStopped() &&
			_pieces[3]->isStopped() );
}

bool Block::hasSpecial(int &x, int &y) {
	for (int i = 0; i < 4; i++)
	if (_pieces[i]->isSpecial()) {
		if ((i == 0) || (i == 2)) {
			x = 0;
		} else {
			x = 1;
		}
		if ( i > 1) {
			y = 1;
		} else {
			y = 0;
		}
		return true;
	}
	return false;
}

GLuint Block::getTexture(const char *name)
{
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (name));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

void Block::Draw() {
	for (int i = 0; i < 4; i++) {
		if (_pieces[i]->isScanned()) {
			return;
		}
	}    

	if ((!isScoreTarget() )) {
		return;
	} else {
		glLoadIdentity();
		        
		glTranslatef( (GLfloat)_x,(GLfloat)_y, -4.99999f );
		GLuint texture = 0;         
		if (_pieces[0]->getColor() == 0) {
			glColor3f(0.75f,0.375f,0.0f);
			texture = getTexture(BLOCK_COLOR0);
		} else {
			glColor3f(0.5f,0.5f,0.5f);
			texture = getTexture(BLOCK_COLOR1);            
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, texture);

		glColor3f(1.0f,1.0f,1.0f);
		
		_quad.setZ(1.0f);
		_quad.setDimensionAndPosition2D(_dim,0.0f, 2.0f * _dim);
		_quad.Draw();

		glDisable(GL_TEXTURE_2D);        	
	}
}

Block& Block::operator= (const Block& param)
{
	_pieces[0] = param._pieces[0];
	_pieces[1] = param._pieces[1];
	_pieces[2] = param._pieces[2];
	_pieces[3] = param._pieces[3];
	_whole = param._whole;
	_boardpos = param._boardpos;
	_inmotion = param._inmotion;
	_x = param._x;
	_y = param._y;
	_dim = param._dim;
	return *this;
}
