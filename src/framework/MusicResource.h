#ifndef MUSICRESOURCE_H_
#define MUSICRESOURCE_H_

#include <string>
#include "SDL.h"
#include "SDL_mixer.h"
#include "GenericResource.h"
#include "AudioInfo.h"


using namespace std;

class MusicResource : public GenericResource<void *> {
public:
	MusicResource(void *info, std::string resourceFile);
  virtual ~MusicResource();
	bool load();
	bool release();
	AudioInfo *getAudioInfo() { return audioInfo; };
private:
	AudioInfo *audioInfo;
};

#endif /*MUSICRESOURCE_H_*/
