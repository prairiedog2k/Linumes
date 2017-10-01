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
#include "TimePositioned.h"
#include <iostream>
float TimePositioned::getDistance(int direction, int current)
{
  float dist = 0.0f;
  float rate = (direction == TimePositioned::DIR_X) ? _xrate : _yrate;
  
  if (canMove(current) )
  {
    dist = ( ( current - _initialTime  )* rate );
    _initialTime = current;
    _wait = 0;
  }
  return dist;
}

float TimePositioned::forecastY(int current)
{
  if (_stopped)
  {
    return _y;
  }
  return _y + getDistance(TimePositioned::DIR_Y, current);
}

float TimePositioned::forecastX(int current)
{
  if (_stopped)
  {
    return _x;
  }
  return _x + getDistance(TimePositioned::DIR_X, current);
}
