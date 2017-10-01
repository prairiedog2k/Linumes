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
#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GenericResource.h"
#include "TextureInfo.h"


using namespace std;

class TextureResource : public GenericResource<GLuint> {
public:
	//texture types
	static const int TEX_TYPE_INVALID = -1;
	static const int TEX_TYPE_BMP     =  0;
	static const int TEX_TYPE_PNG     =  1;

	TextureResource(void *info, std::string resourceFile) : GenericResource<GLuint>(resourceFile), textureInfo((TextureInfo *)info) {};
  virtual ~TextureResource();
	bool load();
	bool release();
private:	
	TextureInfo *textureInfo;
	GLuint loadPNG();
	GLuint loadBMP();
	int getTextureType();
};
#endif
