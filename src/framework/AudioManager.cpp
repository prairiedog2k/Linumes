#include "AudioManager.h"
#include <cassert>
#include "AudioResource.h"
#include "ResourceHelper.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <cmath>

#ifndef MING_NO_PLUGIN
extern "C" {
	void music_mixer(void *udata, Uint8 *stream, int len);
}
#endif

void AudioManager::mixer_monitor(void *udata, Uint8 *_stream, int _len) {

	//mix the music first.
#ifndef MING_NO_PLUGIN
	music_mixer(udata, _stream, _len);
#endif
	if ( NULL != udata) {
		AudioManager *am = (AudioManager *)udata;
		am->calc_freq((Sint16 *)_stream);
	}
}

float AudioManager::getSoundLevel(int band) {
	int level = levels[band];
	int maxLevel = levelsMax[band];
	if (level >= maxLevel) {
		if (level <= 0.01f) {
			return 0.0f;
		}
		levelsMax[band] = level;
		return 1.0f;
	}
	return ((float)(float(level)/float(maxLevel)));
}

void AudioManager::calc_freq(Sint16 *src)
{
	int i;
	Sint16 *d, *sl, *sr, tmp[512];
	float tmp_out[257];

	d = tmp;
	sl = &src[0];
	sr = &src[512];
	for(i = 0; i < 512; i++)
	{
		*(d++) = (*(sl++) + *(sr++)) >> 1;
	}

	fft_perform(tmp,tmp_out,state);
	int currLevel = 0;
	float scale =  256  / log(256);
	for(i = 0; i < 256; i++) {
		currLevel = ((int)(sqrt(tmp_out[i + 1]))) >> 8;
		currLevel >>= 7;
		if(currLevel != 0) {
			currLevel = (int)(log(currLevel) * scale);
		}
		levels[i] = currLevel;
	}
}


AudioManager::AudioManager() : Themed(), _lastChannel(2)
{
}

AudioManager::~AudioManager()
{
#ifndef MING_NO_PLUGIN
	Mix_HookMusic( NULL,NULL );
#else
	Mix_SetPostMix (NULL, NULL );
#endif
}

void AudioManager::init() {
	for (int i = 0 ; i < 256; i++) {
		levels[i] = 0;
		levelsMax[i] = 0;
	}
	state = fft_init();
#ifndef MING_NO_PLUGIN
	Mix_HookMusic( AudioManager::mixer_monitor,this );
#else
	Mix_SetPostMix (AudioManager::mixer_monitor, this );
#endif
}

bool AudioManager::hasBeat(unsigned int currTime) {
	int songTime = ( currTime - _startTick ) % _trackLength;
	if ((songTime >= _nextBeat - 5 ) && (songTime <= _nextBeat + 5)) {
		_lastBeat = _nextBeat;
		_nextBeat = _musicResource->getAudioInfo()->getNextBeat();
		return true;
	}
	return false;
}

std::string AudioManager::getArtist() {
	assert(_theme);
	return _musicResource->getAudioInfo()->getArtist();
}

std::string AudioManager::getTrack() {
	assert(_theme);
	return _musicResource->getAudioInfo()->getTrack();
}

void AudioManager::checkTheme() {
	assert(_theme);
}

void AudioManager::stopSong() {
	checkTheme();
	Mix_MusicType type = MUS_NONE;
	type = _musicResource->getAudioInfo()->getType();
	if (type == MUS_WAV) {
		Mix_HaltChannel(1);
	} else if (type == MUS_MP3) {
		Mix_HaltMusic();
	}
}

void AudioManager::playSong(std::string song) {
	checkTheme();
	Mix_HaltChannel(1);
	_musicResource = ResourceHelper::getMusicResource(_theme,song);

	if ( NULL != _musicResource) {
		Mix_MusicType type = MUS_NONE;
		if (_musicResource->getAudioInfo() != NULL) {
			_trackLength = _musicResource->getAudioInfo()->getSongLength();
			_musicResource->getAudioInfo()->resetBeats();
			_nextBeat = _musicResource->getAudioInfo()->getNextBeat();
			_lastBeat = 0;
			type = _musicResource->getAudioInfo()->getType();
		}

		if (type == MUS_WAV) {
			if(Mix_PlayChannel(1, (Mix_Chunk *)_musicResource->getResource(), -1)==-1) {
#ifdef DEBUG
				std::cout << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
#endif
			}
		} else if (type == MUS_MP3) {
			if(Mix_PlayMusic((Mix_Music *)_musicResource->getResource(), -1)==-1) {
#ifdef DEBUG
				std::cout << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
#endif
			}
		}
		_startTick = SDL_GetTicks();
	}
}

void AudioManager::playAudioResource( AudioResource *resource) {
	if ( NULL != resource) {
		Mix_HaltChannel(_lastChannel);
		if(Mix_PlayChannel(_lastChannel, resource->getResource(), 0)==-1) {
#ifdef DEBUG
			std::cout << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
#endif
		}
		_lastChannel++;
		if (_lastChannel > 15) {
			_lastChannel = 2;
		}
	}
}

void AudioManager::playSoundEffect(std::string sound) {
	checkTheme();
	AudioResource *resource = ResourceHelper::getAudioResource(_theme,sound);
	playAudioResource(resource);
}
