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
#include "ThemeManager.h"
#include "XMLThemeManagerTypes.h"
#include "XMLThemeTypes.h"
#include "xmlParser.h"
#include "Theme.h"
#include "XMLTheme.h"

#ifdef MING_UNISTD
#include "unistd.h"
#endif

ThemeManager::ThemeManager(): themesFile(DEFAULT_FILE) {
	_baseTheme = NULL;
	_currentTheme = NULL;
}

ThemeManager::ThemeManager(std::string filename) : themesFile(filename) {
	_baseTheme = NULL;
	_currentTheme = NULL;
}

ThemeManager::~ThemeManager() {
	if (NULL != _currentTheme) {
		_currentTheme->release();
		delete _currentTheme;
	}
	if (NULL != _baseTheme) {
		_baseTheme->release();
		delete _baseTheme;
	}
}

bool ThemeManager::initData() {
	bool bRetVal = false;
	char currdir[1000];
	getcwd(currdir,1000);
	strcat(currdir,"/");
	FILE *file = fopen(themesFile.c_str(),"r");
	if (file)
	{
		char buff[1000];
		while (! feof(file))
		{
			fgets(buff,1000,file);
			char *target = strtok(buff,"\n");
			if (target)
			{
				std::string val(target);
				themeList.push_back(std::make_pair(val,std::string("")));         
			}
		}
		fclose(file);
		themeIterator = themeList.begin();
		bRetVal = true;
	}
	else
	{
		printf("Theme Manager Could not find file.\n");
	}
	return bRetVal;	
}



bool ThemeManager::initXML() {
	bool bRetVal = false;
	if (NULL == _currentTheme) {
		XMLNode xMainNode=XMLNode::openFileHelper(themesFile.c_str(),THEMELIST_MAIN);
		if (! xMainNode.isEmpty()) {
			XMLNode themeInfo;
			int i = 0;
			do {	 	
				themeInfo = xMainNode.getChildNode(THEMELIST_INFO, &i);
				if (! themeInfo.isEmpty() ) {
					std::string strName( themeInfo.getAttribute(THEMELIST_ATTR_NAME) );
					std::string strFile( themeInfo.getAttribute(THEMELIST_ATTR_FILE) );
					std::string strDir( NULL == themeInfo.getAttribute(THEMELIST_ATTR_DIR) ? "" :  themeInfo.getAttribute(THEMELIST_ATTR_DIR) );
					nameList.push_back(std::make_pair(strName,strFile));
					themeList.push_back(std::make_pair(strFile,strDir));				
				}
			} while ( ! themeInfo.isEmpty() );
			themeIterator = themeList.begin();
			bRetVal = true;

			int themeNode = 0;
			//The base theme is going to persist throughout the execution of the application.
			//and will only be deleted when the application exits.
			XMLNode baseThemeNode = xMainNode.getChildNode(THEME_MAIN, &themeNode);
			if ( ! baseThemeNode.isEmpty() ) {
				_baseTheme = new XMLTheme();
				((XMLTheme *)_baseTheme)->loadResourcesFromNode(baseThemeNode);
			}
		}
		_currentTheme = getNextTheme();		
	}
	return bRetVal;
}

bool ThemeManager::init()
{
	if (themesFile.find(".xml") >= 0) {
		return initXML();
	} else {
		std::cout << "Theme loading via " << DEFAULT_FILE << " is outdated.  Please consider using an XML format." << endl;
		return initData();
	}
}
Theme *ThemeManager::getNamedTheme(std::string themeName) {
	if (themeName.length() == 0) {
		return NULL;
	}
	std::string fileName;
	for (std::list< std::pair<std::string,std::string> >::iterator iter = nameList.begin(); iter != nameList.end(); iter++) {
		if ((*iter).first.compare(themeName) == 0) {
			fileName = (*iter).second;
			break;
		}
	}

	if (fileName.length() == 0) {
		return NULL;
	}

	if (fileName.length() > 0) {
		if (NULL != _currentTheme) {
			_currentTheme->release();
			delete _currentTheme;
			_currentTheme = NULL;
		}

		for (std::list< std::pair<std::string,std::string> >::iterator iter = themeList.begin(); iter != themeList.end(); iter++) {
			if (fileName.compare( (*iter).first) == 0 ) {
				if (NULL != _currentTheme) {
					_currentTheme->release();
					delete _currentTheme;
					_currentTheme = NULL;
				}
				pair<std::string,std::string> filedirpair = *iter;
				if (filedirpair.second == "") {
					_currentTheme = new XMLTheme(filedirpair.first);
				} else {
					_currentTheme = new XMLTheme(filedirpair.first, filedirpair.second);
				}
				_currentTheme->setBaseTheme(_baseTheme);
				_currentTheme->init();
				return _currentTheme;
			}
		}	
	}
	return NULL;
}

Theme *ThemeManager::getNextTheme() {
	if (NULL != _currentTheme) {
		_currentTheme->release();
		delete _currentTheme;
		_currentTheme = NULL;
	}
	pair<std::string,std::string> filedirpair = *themeIterator;

	if (filedirpair.first.find(".xml") >= 0) {
		if (filedirpair.second == "") {
			_currentTheme = new XMLTheme(filedirpair.first);
		} else {
			_currentTheme = new XMLTheme(filedirpair.first, filedirpair.second);
		}
	} else {
		_currentTheme = new Theme(filedirpair.first);
	}
	themeIterator++;
	if (themeIterator == themeList.end()) {
		themeIterator = themeList.begin();
	}  
	_currentTheme->setBaseTheme(_baseTheme);
	_currentTheme->init();
	return _currentTheme;
}
