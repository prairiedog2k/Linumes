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
#ifndef TIME_POSITIONED_H
#define TIME_POSITIONED_H

#include "Timed.h"
#include "Positioned.h"

class TimePositioned: public Timed, public Positioned
{
public:
  static const int DIR_X=0;
  static const int DIR_Y=1;

  float forecastX(int current);
  float forecastY(int current);

  void setXRate( float rate) { _xrate = rate; };
  void setYRate( float rate) { _yrate = rate; };

  TimePositioned( float x, float y, float xrate, float yrate,
                  int current, int wait, bool stopped):
                    Timed(current, wait, stopped),
                    Positioned(x,y),
                    _xrate(xrate), 
                    _yrate(yrate) {};
  virtual ~TimePositioned() {};                    
protected:
  float _xrate;
  float _yrate;

  float getDistance(int direction, int current);
};
#endif
