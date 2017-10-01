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
#ifndef POSITIONED_H
#define POSITIONED_H


using namespace std;

class Positioned {
protected:
  float _x;
  float _y;
public:
  Positioned();
  Positioned(float x, float y);
  virtual ~Positioned() {};
  const float getY() { return _y;};
  const float getX() { return _x;};
  void setX(const float x) { _x = x; };
  void setY(const float y) { _y = y; };
  void setPiecePos (const float x, const float y) { _x = x; _y = y; };
};
#endif
