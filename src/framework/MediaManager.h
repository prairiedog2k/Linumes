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
#ifndef MEDIA_MANAGER_H
#define MEDIA_MANAGER_H

#include "SDL.h"
#include "Configuration.h"

namespace Hunchback::Framework {

class MediaManager
{
private:
	static int screenheight;
	static int screenwidth;
	static SDL_Window *_window;

	int screenbpp;
	bool _fullscreen;
	SDL_GLContext glContext;
	SDL_Joystick *joystick;

	void initSDL();
	void initCursor();
	void initJoyStick();
	void initAudio();
	void initGraphics();
	void initFont();
	bool initGL();
public:
	MediaManager(int width, int height, int bpp);
	MediaManager(Configuration configuration);
	~MediaManager();
	void resizeWindow( int width, int height );
	void toggleFullScreen();
	bool init();
	void release();
	bool resizeScreenTo(int width, int height);
	void takeScreenShot();
	SDL_Joystick *getJoyStick() { return joystick; };
	static int getScreenHeight() { return screenheight; };
	static int getScreenWidth()  { return screenwidth;  };
	static SDL_Window* getWindow() { return _window; };
	void resetGlContext() { initGL(); resizeWindow(getScreenWidth(), getScreenHeight()); };
};

} // namespace Hunchback::Framework

#endif
