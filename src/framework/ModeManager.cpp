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
#include <iostream> 
#include "ModeManager.h"
#include <cassert>
#include <cstdlib>

#include "ScreenDimensions.h"

ModeManager::ModeManager(): currMode(0), isActive(true), isDone(false) 
{
	mediamanager = new MediaManager(SCREEN_DIM_W,SCREEN_DIM_H,SCREEN_DIM_BPP);
	mediamanager->init();
}

ModeManager::ModeManager(std::string configurationFile) : currMode(0), isActive(true), isDone(false),configuration(configurationFile)
{
	configuration.init();
	mediamanager = new MediaManager(configuration);
	mediamanager->init();

}

ModeManager::~ ModeManager()
{

	if (currMode != NULL) {
		delete currMode;
	}

	configuration.release();

	if (mediamanager != NULL) {
		mediamanager->release();
		delete mediamanager;
	}
}

bool ModeManager::init()
{
	isActive = false;

	if ( !initContext() ) { return false; }

	isActive = true;
	return true;
}

bool ModeManager::release() {
	return true;
}

void ModeManager::run()
{
	SDL_Event event;	
	bool proceed = true;

	Sint16 xAxis = 0;
	Sint16 yAxis = 0;
	Sint16 zBtn = 0;
	Sint16 xBtn = 0;
	Sint16 retBtn = 0;
	Sint16 bkspBtn = 0;	
	Sint16 lastXDir = 0;
	Sint16 lastYDir = 0;
	
	SDL_Joystick* joy = mediamanager->getJoyStick();
	
	SDL_keysym joyKey = { 0, SDLK_UNKNOWN, KMOD_NONE, 0};
	
	while (!isDone)
	{
		assertValidMode();  	
		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_ACTIVEEVENT:
				/* Something's happend with our focus
				 * If we lost focus or we are iconified, we
				 * shouldn't draw the screen
				 */
				//        if ( event.active.gain == 0 )
				//        {
				//          isActive = false;
				//        }
				//        else
				//        {
				//          isActive = true;
				//        }
				isActive = true;
				break;
			case SDL_VIDEORESIZE:
				if ( ! mediamanager->resizeScreenTo(event.resize.w,
						event.resize.h) )
				{
					isActive=false;
					isDone=true;
				}
				break;
			case SDL_JOYAXISMOTION:
				xAxis = SDL_JoystickGetAxis(joy,0);
				yAxis = SDL_JoystickGetAxis(joy,1);
				if (xAxis != 0) {
					if (xAxis < 0) {
						joyKey.sym = SDLK_LEFT;
						handleKeyDown( &joyKey);
						lastXDir = -1;
					}
					if (xAxis > 0) {
						joyKey.sym = SDLK_RIGHT;
						handleKeyDown( &joyKey);
						lastXDir = 1;
					}
				} else {
					if (lastXDir > 0) {
						joyKey.sym = SDLK_RIGHT;
						handleKeyUp( &joyKey);
					}
					if (lastXDir < 0) {
						joyKey.sym = SDLK_LEFT;
						handleKeyUp( &joyKey);
					}
					lastXDir = 0;
				}
				if (yAxis != 0) {
					if (yAxis < 0) {
						joyKey.sym = SDLK_UP;
						handleKeyDown( &joyKey);
						lastYDir = -1;
					}
					if (yAxis > 0) {
						joyKey.sym = SDLK_DOWN;
						handleKeyDown( &joyKey);
						lastYDir = 1;
					}
				} else {
					if (lastYDir > 0) {
						joyKey.sym = SDLK_DOWN;
						handleKeyUp( &joyKey);
					}
					if (lastYDir < 0) {
						joyKey.sym = SDLK_UP;
						handleKeyUp( &joyKey);
					}
					lastYDir = 0;
				}
				joyKey.sym = SDLK_UNKNOWN;
				break;
			case SDL_JOYBUTTONDOWN:
				zBtn = SDL_JoystickGetButton(joy,0);
				if (zBtn == 1) {
					joyKey.sym = SDLK_z;
					handleKeyDown( &joyKey);
				}
				xBtn = SDL_JoystickGetButton(joy,1);
				if (xBtn == 1) {
					joyKey.sym = SDLK_x;
					handleKeyDown( &joyKey);
				}
				retBtn = SDL_JoystickGetButton(joy,2);
				if (retBtn == 1) {
					joyKey.sym = SDLK_RETURN;
					handleKeyDown( &joyKey);
				}
				bkspBtn = SDL_JoystickGetButton(joy,3);
				if (bkspBtn == 1) {
					joyKey.sym = SDLK_BACKSPACE;
					handleKeyDown( &joyKey);
				} 
				joyKey.sym = SDLK_UNKNOWN;
				break;
			case SDL_JOYBUTTONUP:
				break;				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_F1:
					mediamanager->toggleFullScreen();
					proceed = false;        	
					break;
				case SDLK_F11:
					isActive = false;
					mediamanager->takeScreenShot();
					isActive = true;
					proceed = false;
				default:
					break;
				}
				if (! proceed) {
					proceed = true;
					break;
				}
				handleKeyDown( &event.key.keysym );
				break;
				case SDL_KEYUP:
					handleKeyUp  ( &event.key.keysym );
					break;
				case SDL_QUIT:
					isDone = true;
					break;
				default:
					break;
			}      
		}

		update();

		if (! isDone ) {    
			if (isActive && !isDone)
			{	
				currMode->update( SDL_GetTicks() );
				isDone = currMode->isDone();
			}
		}
		//slow down the rendering to ~63 FPS
		//SDL_Delay(12);
	}
}

void ModeManager::assertValidMode() {
	assert(currMode);	
}
