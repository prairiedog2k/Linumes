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
#include "Utils.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureResource.h"

#ifdef MING_GL 
#include "GL/glext.h"
#endif

TextureResource::~TextureResource() {
	if (textureInfo != NULL){
		delete textureInfo;
		textureInfo = NULL;
	}
}

GLuint TextureResource::loadPNG()
{
  /* Status indicator */
  bool Status = false;
  /* Create storage space for the texture */
  SDL_Surface *TextureImage[1];
  SDL_Surface *intermediary;
  GLuint pngtexture = 0;
  int w,h;

  /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
  if ( ( TextureImage[0] = IMG_Load( resourceFile.c_str() ) ) )
  {
    /* Convert the rendered text to a known format */
    w = nextpoweroftwo(TextureImage[0]->w);
    h = nextpoweroftwo(TextureImage[0]->h);
    /*
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    */
    intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);    
    //intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0xff000000);
    SDL_BlitSurface(TextureImage[0], 0, intermediary, 0);

    /* Set the status to true */
    Status = true;

    /* Create The Texture */
    glGenTextures( 1, &pngtexture);

    /* Load in texture */
    /* Typical Texture Generation Using Data From The Bitmap */
    glBindTexture( GL_TEXTURE_2D, pngtexture);

    /* Linear Filtering */
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    GLfloat foo = 0.0f;
    glPrioritizeTextures(1,&pngtexture,&foo);
    
    /* Generate The Texture */
    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
                  //TextureImage[0]->h, 0, GL_BGR,
                  TextureImage[0]->h, 0, GL_BGRA,        
                  GL_UNSIGNED_BYTE, intermediary->pixels );
  }
  else
  {
    cout << "Could not load " << resourceFile << " - should exit" << endl;
  }

		  
  /* Free up any memory we may have used */
  if ( TextureImage[0] )
  {
    SDL_FreeSurface( TextureImage[0] );
    SDL_FreeSurface( intermediary );
  }
  return pngtexture;
}

GLuint TextureResource::loadBMP()
{
  /* Create storage space for the texture */
  SDL_Surface *TextureImage[1];
  GLuint bmptexture = 0;
  /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
  if ( ( TextureImage[0] = SDL_LoadBMP(resourceFile.c_str())) )
  {
    /* Create The Texture */
    glGenTextures( 1 , &bmptexture );
    glBindTexture( GL_TEXTURE_2D, bmptexture );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
                  TextureImage[0]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE,
                  TextureImage[0]->pixels );

    /* Linear Filtering */
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                     GL_LINEAR );
  } else {
	cout << "Could not load " << resourceFile << " - should exit" << endl;
  }
  if ( TextureImage[0] )
    SDL_FreeSurface( TextureImage[0] );
  return bmptexture;
}

 int TextureResource::getTextureType() {
  if (resourceFile.find (".bmp",0) != string::npos) {
    return TEX_TYPE_BMP;
  }
  if (resourceFile.find (".png",0) != string::npos) {
    return TEX_TYPE_PNG;
  }
  if (resourceFile.find (".BMP",0) != string::npos) {
    return TEX_TYPE_BMP;
  }
  if (resourceFile.find (".PNG",0) != string::npos) {
    return TEX_TYPE_PNG;
  }
  return TEX_TYPE_INVALID;
}

bool TextureResource::load() {
  int texturetype = getTextureType();
  value_ = 0;
  switch (texturetype) {
	case TEX_TYPE_BMP: {
		value_ = loadBMP();
#ifdef DEBUG
    cout << "Loaded " << resourceFile << endl;
#endif		
		break;
	}
	case TEX_TYPE_PNG: {
		value_ = loadPNG();
#ifdef DEBUG
    cout << "Loaded " << resourceFile << endl;
#endif		
		break;
	}
	default: {
		cout << resourceFile << " was not of a recognizable texture type" << endl;
		break;
	}	
  }
  return (value_ != 0);
}


bool TextureResource::release() {
#ifdef DEBUG
   cout << "release texture sample from ";
   reportResourceFile();
   cout << "Texture Number : " << value_ << endl;
#endif
	glDeleteTextures( 1, &value_ );
	return true;
}
