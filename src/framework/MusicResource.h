#pragma once

#include <string>
#include "SDL.h"
#include "SDL_mixer.h"
#include "GenericResource.h"
#include "AudioInfo.h"

namespace Hunchback::Framework {

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

} // namespace Hunchback::Framework
