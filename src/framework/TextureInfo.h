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
#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class TextureInfo {
private:
  bool _mask;
	GLuint _numTextures;
public:
  TextureInfo();
  virtual ~TextureInfo();
	GLuint getNumberOfTextures() { return _numTextures; };
	void setNumberOfTextures(GLuint numTextures) { _numTextures = numTextures; };
	bool isMasked() { return _mask; };
	void setMasked(bool mask) { _mask = mask; };
};

#endif
