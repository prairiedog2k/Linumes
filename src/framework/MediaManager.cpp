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
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include "MediaManager.h"
#include "MediaConfigurationTypes.h"

int MediaManager::screenheight = 0;
int MediaManager::screenwidth = 0;

MediaManager::MediaManager(int width, int height, int bpp) : screenbpp(bpp) {
	MediaManager::screenheight = height; 
	MediaManager::screenwidth = width;
}

MediaManager::MediaManager(Configuration configuration) {
	MediaManager::screenheight = std::atoi(configuration.getValue(MEDIA_SCREEN_HEIGHT).c_str());
	MediaManager::screenwidth = std::atoi(configuration.getValue(MEDIA_SCREEN_WIDTH).c_str());
	screenbpp = std::atoi(configuration.getValue(MEDIA_SCREEN_BPP).c_str());
}

MediaManager::~MediaManager() {
	
}

void MediaManager::initSDL()
{
  if(SDL_Init(SDL_INIT_AUDIO |SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)< 0)  {
    cout <<"Could not initialize SDL: " << SDL_GetError() << endl;
    SDL_Quit();
  }
  SDL_WM_SetCaption("Linumes - 2008",NULL);
}

void MediaManager::initAudio()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512)==-1)
  {
    cerr << "Mix_OpenAudio: " << Mix_GetError() << endl;
    SDL_Quit();
  }
  Mix_AllocateChannels(16);
  Mix_Volume(1, MIX_MAX_VOLUME/ 2);
  for (int chan = 2; chan < 16; chan++)
  {
    Mix_Volume(chan ,MIX_MAX_VOLUME);
  }
}

void MediaManager::initGraphics()
{
  videoInfo = SDL_GetVideoInfo( );
  if ( !videoInfo )
  {
    cerr << "Video query failed: " << SDL_GetError( ) << endl;
    SDL_Quit();
  }
  /* the flags to pass to SDL_SetVideoMode */
  videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
  videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
  videoFlags |= SDL_OPENGLBLIT;
  videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
  videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */
  //videoFlags |= SDL_FULLSCREEN;       /* Enable window resizing */


  /* This checks to see if surfaces can be stored in memory */
  if ( videoInfo->hw_available )
    videoFlags |= SDL_HWSURFACE;
  else
    videoFlags |= SDL_SWSURFACE;

  /* This checks if hardware blits can be done */
  if ( videoInfo->blit_hw )
    videoFlags |= SDL_HWACCEL;

  /* Sets up OpenGL double buffering */
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  /* get a SDL surface */
  surface = SDL_SetVideoMode( screenwidth, screenheight, screenbpp,
                              videoFlags );

  /* Verify there is a surface */
  if ( !surface )
  {
    cerr << "Video mode set failed: " << SDL_GetError( ) << endl;
    SDL_Quit();
  }

}

/* function to reset our viewport after a window resize */
void MediaManager::resizeWindow( int width, int height )
{
  /* Height / width ration */
  GLfloat ratio;

  /* Protect against a divide by zero */
  if ( height == 0 )
    height = 1;

  ratio = ( GLfloat )width / ( GLfloat )height;

  /* Setup our viewport. */
  glViewport( 0, 0, ( GLint )width, ( GLint )height );

  /*
   * change to the projection matrix and set
   * our viewing volume.
   */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );

  /* Set our perspective */
  gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

  /* Make sure we're chaning the model view and not the projection */
  glMatrixMode( GL_MODELVIEW );

  /* Reset The View */
  glLoadIdentity( );
}

bool MediaManager::initGL()
{
  /* Enable smooth shading */
  glShadeModel( GL_SMOOTH );

  /* Set the background black */
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  /* Depth buffer setup */
  glClearDepth( 1.0f );

  /* Enables Depth Testing */
  glEnable( GL_DEPTH_TEST );

  /* The Type Of Depth Test To Do */
  glDepthFunc( GL_LEQUAL );

  /* Really Nice Perspective Calculations */
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  return true;
}

void MediaManager::initCursor() {
	SDL_ShowCursor(SDL_DISABLE);
}

void MediaManager::initJoyStick() {
	joystick = NULL;
	int numJoy = SDL_NumJoysticks();
	if (numJoy > 0) {
#ifdef DEBUG
		printf ("There %s %d Joystick%s Attached to the Computer\n",  ( numJoy > 1 ? "are" : "is") , numJoy, ( numJoy > 1 ? "s" : "") );

#endif
		
		joystick = SDL_JoystickOpen(numJoy-1);
		if (NULL != joystick) {
#ifdef DEBUG
			printf("\tUsing Joystick %s\n",SDL_JoystickName(numJoy-1));
#endif
			SDL_JoystickEventState(SDL_ENABLE);
		}
	}
}

void MediaManager::initFont()
{
  TTF_Init();
}

bool MediaManager::init()
{
  bool bRetVal = false;
#ifdef MING_RANDOM
  srand(time(0));
#else
  srandom(time(0));
#endif
  initSDL();

  initAudio();

  initGraphics();

  initFont();

  initGL( );

  //initJoyStick();

  resizeWindow( screenwidth, screenheight );
  bRetVal = true;

  return bRetVal;
}

void MediaManager::release()
{
  Mix_CloseAudio();
  TTF_Quit();
  /* clean up the window */
  SDL_Quit( );
}

void MediaManager::toggleFullScreen()
{
  videoFlags ^= SDL_FULLSCREEN;
  surface = SDL_SetVideoMode( screenwidth, screenheight, screenbpp,
                              videoFlags );
}

bool MediaManager::resizeScreenTo( int w, int h) {
	screenwidth = w;
	screenheight = h;
  surface = SDL_SetVideoMode( w,
                              h,
                              screenbpp, videoFlags );
  if ( !surface )
  {
    return false;
  }

  resizeWindow( w, h );

  return true;
}

void MediaManager::takeScreenShot() {
	      static int screenshotCounter = 0;
	      int screenWidth = surface->w;
	      int screenHeight = surface->h;
        char screenshotName[64];
        sprintf(screenshotName, "screenshot%02d.bmp", screenshotCounter++);
        Uint32 rmask, gmask, bmask, amask;
        amask = 0x000000;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff0000;
        gmask = 0x00ff00;
        bmask = 0x0000ff;
#else
        rmask = 0x0000ff;
        gmask = 0x00ff00;
        bmask = 0xff0000;
#endif
        SDL_Surface *temp = SDL_CreateRGBSurface(SDL_SWSURFACE, screenWidth, screenHeight, 24, rmask, gmask, bmask, amask);
        SDL_Surface *image = SDL_CreateRGBSurface(SDL_SWSURFACE, screenWidth, screenHeight, 24, rmask, gmask, bmask, amask);
        glReadBuffer(GL_FRONT);
        glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
        int i;
        for(i = 0; i < screenHeight; i++)
            memcpy((char *)temp->pixels + 3 * screenWidth * i, (char *)image->pixels + 3 * screenWidth * (screenHeight - i), 3 * screenWidth);
        memcpy(image->pixels, temp->pixels, screenWidth * screenHeight * 3);
        SDL_SaveBMP(temp, screenshotName);
        SDL_FreeSurface(image);
        SDL_FreeSurface(temp);
}
