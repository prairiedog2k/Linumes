#include "MusicResource.h"

namespace Hunchback::Framework {

MusicResource::MusicResource(void *info, std::string argResourceFile) :
	GenericResource<void *>(argResourceFile),
	audioInfo((AudioInfo *)info) {
};

MusicResource::~MusicResource() {
  release();
  delete audioInfo;
  audioInfo = nullptr;
}

bool MusicResource::load() {
	if (nullptr == audioInfo) {
		return false;
	}
	if (audioInfo->getType() == MUS_WAV ) {
		value_ = Mix_LoadWAV(resourceFile.c_str());
	} else if (audioInfo->getType() == MUS_MP3) {
		value_ = Mix_LoadMUS(resourceFile.c_str());
	}
#ifdef DEBUG
  std::cout << "load music sample from ";
  reportResourceFile();
#endif
	return value_ != 0;
}

bool MusicResource::release() {
#ifdef DEBUG
   std::cout << "release music sample from ";
   reportResourceFile();
#endif
  if (value_ && audioInfo) {
    if (audioInfo->getType() == MUS_WAV) {
      Mix_FreeChunk((Mix_Chunk *)value_);
    } else if (audioInfo->getType() == MUS_MP3) {
      Mix_FreeMusic((Mix_Music *)value_);
    }
    value_ = nullptr;
  }
  return true;
}

} // namespace Hunchback::Framework
