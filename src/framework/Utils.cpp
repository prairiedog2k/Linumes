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
#include "MediaManager.h"
#include "ScreenDimensions.h"

int roundi(double x)
{
	return (int)(x + 0.5);
}

int nextpoweroftwo(int x)
{
	double logbase2 = log((double)x) / log((double)2);
	return roundi(pow(2,ceil(logbase2)));
}

/* Quick utility function for texture creation */
int power_of_two(int input)
{
        int value = 1;

        while ( value < input ) {
                value <<= 1;
        }
        return value;
}

int xformX(int x) {
	return (int)( (float((float)(x) / (float)(SCREEN_DIM_W)) * MediaManager::getScreenWidth()) );
}

int xformY(int y) {
	return (int)( (float((float)(y) / (float)(SCREEN_DIM_H)) * MediaManager::getScreenHeight()) );
}


