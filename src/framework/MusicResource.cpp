#include "MusicResource.h"

MusicResource::MusicResource(void *info, string argResourceFile) : 
	GenericResource<void *>(argResourceFile), 
	audioInfo((AudioInfo *)info) {
};

MusicResource::~MusicResource() {
  if (audioInfo != NULL) {
    delete audioInfo;
  }
}

bool MusicResource::load() {
	if (NULL == audioInfo) {
		return false;
	}
	if (audioInfo->getType() == MUS_WAV ) {
		value_ = Mix_LoadWAV(resourceFile.c_str());
	} else if (audioInfo->getType() == MUS_MP3) {
		value_ = Mix_LoadMUS(resourceFile.c_str());
	}
#ifdef DEBUG
  cout << "load music sample from ";
  reportResourceFile();
#endif	
	return value_ != 0;
}

bool MusicResource::release() {
#ifdef DEBUG
   cout << "release music sample from ";
   reportResourceFile();
#endif
  if (value_ != 0) {
  	if (audioInfo->getType() == MUS_WAV ) {
			Mix_FreeChunk((Mix_Chunk *)value_);
		} else if (audioInfo->getType() == MUS_MP3) {
			Mix_FreeMusic((Mix_Music *)value_);
		}
  }
	return value_ == 0;
}


