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
#include "Theme.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "TextureResource.h"
#include "AudioResource.h"
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

namespace Hunchback::Framework {

Theme::Theme(std::string filename): themefile(filename), _baseTheme(nullptr) {
};

Theme::~Theme()
{
	release();
}

void Theme::handleTag(const char *cwd, const char* tag, const char *target)
{
	if ( !cwd || !tag || !target)
	{
		return;
	}
	std::string strCwd(cwd);
	std::string strTag(tag);
	std::string strTarget(target);
	if (strTag == "dir")
	{
		strCwd += strTarget;
		strCwd += "/";
		themedir = strCwd;
	}

	std::string resourceFile = themedir + target;

	if ( themedir.size() > 0)
	{
		if ( strTag.at(0) == 'a')
		{
			resourceCount++;
			AudioResource *ar = new AudioResource(nullptr, resourceFile);
			ar->load();
			resources[tag]= ar;
		}
		if ( strTag.at(0) == 't')
		{
			resourceCount++;
			TextureResource *tr = new TextureResource(nullptr,resourceFile);
			tr->load();
			resources[tag] = tr;
		}
		if ( strTag.at(0) == 'f')
		{
			printf("Font\n");
			fontfile=strTarget;
		}
	}
}

BaseResource *Theme::getResource(std::string target) {
	auto it = resources.find(target);
	return (it != resources.end()) ? it->second : nullptr;
}

bool Theme::init()
{
	resourceCount = 0;
	
	char currdir[1000];
	getcwd(currdir,1000);
	strcat(currdir,"/");
	FILE *file = fopen(themefile.c_str(),"r");
	if (file)
	{
		char buff[1000];
		while (! feof(file))
		{
			fgets(buff,1000,file);
			char *tag = strtok(buff,"=");
			if (tag)
			{
				char* target = strtok(nullptr,"\n");
				if (target)
				{
					handleTag(currdir,tag,target);
				}
			}
		}
		fclose(file);
	}
	else
	{
		std::cout << "Could not find file " << themefile << std::endl;
	}
	return resourceCount > 0;
}


void Theme::release()
{
	if (resources.empty()) return;
	for (auto& [key, resPtr] : resources) {
		delete resPtr;
	}
	resources.clear();
	resourceCount = 0;
#ifdef DEBUG
	std::cout << "Theme Release Complete. " << std::endl;
#endif
}

} // namespace Hunchback::Framework

