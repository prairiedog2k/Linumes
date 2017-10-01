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
#ifndef TIMED_H
#define TIMED_H

#include <iostream>

using namespace std;
class Timed
{
protected:
  int _initialTime;
  int _wait;
  bool _stopped;

public:
  Timed():_initialTime(0), _wait(0), _stopped(true) {};
  Timed(int current, int timewait, bool isStopped): _initialTime(current),_wait(timewait),_stopped(isStopped) {};
  virtual ~Timed() {};
  bool canMove(int current);
  virtual bool isStopped(){ return _stopped;};
  void setStopped( bool stopped ) { stopped = stopped; };
  void setInitialTime( int time ) { _initialTime = time; };
  void setWait(int timewait) { _wait = timewait; };
};

#endif
