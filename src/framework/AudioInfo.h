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
#ifndef AUDIO_INFO_H
#define AUDIO_INFO_H
#include <string>
#include <list>
#include "SDL_mixer.h"

using namespace std;

class AudioInfo {
private:
	std::string _mixer;
	Mix_MusicType _type;
	//contains beat location in milliseconds from the beginning of the song
	std::list<int> beatSequence;
	//the current beat time in milliseconds from the beginning of the song.
	std::list<int>::iterator beat;
	//song length in milliseconds
	int  _songLength;
	//whether or not prepare has been called
	bool _wasInit;
	
	std::string _artist;
	std::string _track;
	
public:
  AudioInfo();
  ~AudioInfo(); 
	void setMixer(std::string mixer) { _mixer = mixer; };
	void setType(Mix_MusicType type) { _type = type; };
	Mix_MusicType getType() { return _type; }; 
	std::string getMixer() { return _mixer; };
	void addTiming(int beatTime);
	bool prepare();
	int getNextBeat();
	int getBeatCount();
	void setSongLength(int songLength) { _songLength = songLength; };
	int getSongLength() { return _songLength; };
	void resetBeats() { _wasInit = false; prepare(); };
	std::string getArtist() { return _artist; };
	std::string getTrack() { return _track; };
	void setArtist( std::string artist) { _artist = artist; };
	void setTrack (std::string track) { _track = track; };
};
#endif


