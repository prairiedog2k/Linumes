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
#include "AudioResource.h"


AudioResource::AudioResource(void *info, string argResourceFile) : GenericResource<Mix_Chunk *>(argResourceFile), audioInfo((AudioInfo *)info) {
};

AudioResource::~AudioResource() {
  if (audioInfo != NULL) {
    delete audioInfo;
  }
}


bool AudioResource::load() {
	value_ = Mix_LoadWAV(resourceFile.c_str());
#ifdef DEBUG
  cout << "load audio sample from ";
  reportResourceFile();
#endif	
	return value_ != 0;
}

bool AudioResource::release() {
#ifdef DEBUG
   cout << "release audio sample from ";
   reportResourceFile();
#endif
  if (value_ != 0) { 	
		Mix_FreeChunk(value_);
  }
	return value_ == 0;
}

