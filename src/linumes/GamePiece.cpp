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

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"

#include "GamePiece.h"
#include "PieceTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"

GamePiece::GamePiece() : Rendered(true),
TimePositioned(0.0f, 0.0f, 0.0f, 0.0f, 0,0,false), 
_dim(1.0),
_edge(0.0f),
_scoreTarget(false),
_overlap(false),
_scanned(false),
_fallto(0.0),
_special(false),
_visited(false),
_connected(false),
_quad()
{
}

GamePiece::GamePiece(float x, float y, float dim, float edge) : Rendered(true),
TimePositioned( x, y, 0.0f, 0.0f, 0,0,false),
_dim(dim),
_edge(edge),
_scoreTarget(false),
_overlap(false),
_scanned(false),
_fallto(0.0),
_special(false),
_visited(false),
_connected(false),
_nexty(y),
_quad()
{
#ifdef MING_RANDOM    
	_color = rand() % 2;
#else
	_color = random() % 2;
#endif  
}

GamePiece::GamePiece(const GamePiece &piece): Rendered(piece._renderable),
TimePositioned( piece._x, piece._y, 0.0f, 0.0f, 0,0,piece._stopped), Themed(piece),	 
_dim(piece._dim),
_edge(piece._edge),
_color(piece._color),
_scoreTarget(piece._scoreTarget),
_overlap(piece._overlap),
_scanned(piece._scanned),
_fallto(piece._fallto),
_special(piece._special),
_visited(piece._visited),
_connected(piece._connected),
_nexty(piece._nexty),
_quad()
{
}

bool GamePiece::setNewColor(bool CanSpecial)
{
#ifdef MING_RANDOM
	_color = rand() % 2;
#else
	_color = random() % 2;
#endif
	_special = CanSpecial;
	_connected = false;
	_visited = false;
	return _special;
}

GamePiece::~GamePiece()
{}


GLuint GamePiece::getTexture(const char *name)
{
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (name));
	if (NULL == tr) {
#ifdef DEBUG
		std::cout << " texture miss : " << name << std::endl;
#endif 		
		return 0;
	}
	return tr->getResource();
}

bool GamePiece::hasMask() {
	return (NULL != ResourceHelper::getTextureResource(getTheme(), std::string (  _color == 0 ? PIECE_MASK0 : PIECE_MASK1 ) ) );
}

void GamePiece::bindMask() {
	const char *strState = NULL;
	if ( _color == 0)
	{
		strState = PIECE_MASK0;
	} else {
		strState = PIECE_MASK1;
	}
	glBindTexture( GL_TEXTURE_2D, getTexture((const char *)strState));

	glColor3f(1.0f,1.0f,1.0f);
}

void GamePiece::bindStateTexture()
{
	const char *strState = NULL;
	if ( _color == 0)
	{
		if (_scanned || _special || _connected) {
			if (_scanned || _connected)
			{
				strState = PIECE_SCANNED0;
			} else if (_special)
			{
				strState = PIECE_SPECIAL0;
			}
		}
		else
		{
			strState = PIECE_COLOR0;
		}
	}
	else
	{
		if (_scanned || _special || _connected) {
			if (_scanned || _connected)
			{
				strState = PIECE_SCANNED1;
			} else if (_special)
			{
				strState = PIECE_SPECIAL1;
			}
		}
		else
		{
			strState = PIECE_COLOR1;
		}
	}	
	
	glBindTexture( GL_TEXTURE_2D, getTexture((const char *)strState));

	glColor3f(1.0f,1.0f,1.0f);
}


void GamePiece::Dump() {
	std::cout << "\tx,y,dim " << this->getX() << ", " << this->getY() << ", " << this->getDimension() << std::endl;
}

void GamePiece::Draw()
{
	if (isRenderable())
	{
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		
		glTranslatef( (GLfloat)_x,(GLfloat)_y, -5.0f );

		_quad.setZ(1.0f);
		_quad.setDimensionAndPosition2D((_dim - _edge )/2.0f,(_dim - _edge )/2.0f, (_dim - _edge ) );

		if (hasMask()) {
			glEnable(GL_BLEND);
			bindMask();
			glBlendFunc(GL_DST_COLOR,GL_ZERO);
			_quad.Draw();
			
			bindStateTexture();
			glBlendFunc(GL_ONE, GL_ONE);
			_quad.Draw();
			glDisable(GL_BLEND);
		} else {
			bindStateTexture();
			_quad.Draw();
		}
		

		glDisable(GL_TEXTURE_2D);
	}
}

GamePiece& GamePiece::operator= (const GamePiece& param)
{
	if ( this != &param) {
		_color = param._color;
		_dim = param._dim;
		_x = param._x;
		_y = param._y;
		_nexty = param._nexty;
		_stopped = param._stopped; 
		_scoreTarget=param._scoreTarget;
		_overlap=param._overlap;
		_scanned=param._scanned;
		_renderable=param._renderable;
		_fallto=param._fallto;
		_special = param._special;
		_visited = param._visited;
		_connected = param._connected;
	}
	return *this;
}

void GamePiece::copyPieceState( GamePiece *param) {
	if ((this != param) && (param != NULL)) {
		_color = param->_color;
		_stopped = param->_stopped; 
		_scoreTarget=param->_scoreTarget;
		_overlap=param->_overlap;
		_scanned=param->_scanned;
		_renderable=param->_renderable;
		_fallto=param->_fallto;
		_special = param->_special;
		_visited = param->_visited;
		_connected = param->_connected;
	}
}

void GamePiece::update(unsigned int currTime) {
	_y = forecastY( currTime );
	if ( (_y <= _nexty) ) {
		_y = _nexty;			
	}	
}

bool GamePiece::isStopped() {
	int nexty = (int) ( 1000 * _nexty);
	int y = (int) ( 1000 * _y);	
	return (nexty == y);
}

