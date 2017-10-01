#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <string>
#include "Themed.h"
#include "MusicResource.h"
#include "AudioResource.h"
#include "fft.h"
using namespace std;

class AudioManager: public Themed
{
private:
	int _lastChannel;
	int _startTick;
	int _nextBeat;
	int _lastBeat;
	int _trackLength;
	
	int levels[256];
	int levelsMax[256];
	MusicResource *_musicResource;
	
public:
	AudioManager();
	virtual ~AudioManager();
	static void timeSong(int chan, void *stream, int len, void *udata);
	void init();
  void playSong(std::string song);
  void stopSong();
  bool hasBeat(unsigned int currTime);
  int getLastBeat() { return _lastBeat;};
  int getNextBeat() { return _nextBeat;};
  void playSoundEffect(std::string effect);
  void playAudioResource( AudioResource *resource);
  std::string getArtist();
  std::string getTrack();
  float getSoundLevel(int band);
private:
  void checkTheme();
  void calc_freq(Sint16 *_stream);  
  fft_state *state;
  //begin static 
public:
  static void mixer_monitor(void *udata, Uint8 *_stream, int _len);
};

#endif /*AUDIOMANAGER_H_*/
