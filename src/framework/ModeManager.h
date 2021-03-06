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
#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H


#include "SDL.h"
#include <string>

#include "MediaManager.h"
#include "ThemeManager.h"
#include "Mode.h"
#include "Configuration.h"

using namespace std;

class ModeManager {

protected:
	Mode *currMode;
	virtual bool initContext() = 0;
	virtual void update() = 0;
	virtual void handleKeyUp( SDL_keysym *keysym ) = 0;
	virtual void handleKeyDown( SDL_keysym *keysym ) = 0;   

	bool isActive;
	bool isDone;

	MediaManager *mediamanager;
	Configuration configuration;
public:
	ModeManager();
	ModeManager(std::string configurationFile);

	virtual ~ModeManager();

	virtual bool init();
	virtual bool release();
	void run(); 
 
private: 
	void assertValidMode();
};

#endif
