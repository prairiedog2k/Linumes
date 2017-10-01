#include "AudioInfo.h"

AudioInfo::AudioInfo() :  _type(MUS_NONE), _wasInit(false) {
}

AudioInfo::~AudioInfo() {
}

bool AudioInfo::prepare() {
  if (_wasInit) {
    return _wasInit;
  }
  
  if (beatSequence.size() > 0) {
    beat = beatSequence.begin();
    _wasInit = true;
  }
  return _wasInit;
}

void AudioInfo::addTiming(int beatTime) {
  //only accept new timing while  
  //`prepare` has not been called
  if (!_wasInit ) {
    beatSequence.push_back(beatTime); 
  }
}

int AudioInfo::getNextBeat() {
  int retVal = *beat;
  beat++;
  if (beat == beatSequence.end()) {
    beat = beatSequence.begin();
  }
  return retVal;
}

int AudioInfo::getBeatCount() {
  return beatSequence.size();
}
