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
#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <string>
#include <list>
#include "Theme.h"

#define DEFAULT_FILE "theme.list"

using namespace std;

class ThemeManager{
protected:
  Theme *_baseTheme;
  Theme *_currentTheme;
public:
  ThemeManager();
  ThemeManager(std::string filename);
  virtual ~ThemeManager();
  virtual bool init();
  Theme *getNamedTheme(std::string themeName);
  Theme *getNextTheme();
  Theme *getBaseTheme() { return _baseTheme; };
  Theme *getCurrentTheme() { return _currentTheme; };
private:
  bool initXML();
  bool initData();
  
  std::string themesFile;
  std::list< std::pair< std::string, std::string> > nameList;    
  std::list< std::pair< std::string, std::string> > themeList;  
  std::list< std::pair< std::string, std::string> >::iterator themeIterator; 
};
#endif
