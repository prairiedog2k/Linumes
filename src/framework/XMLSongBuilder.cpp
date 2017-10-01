#include "XMLSongBuilder.h"
#include "XMLSongTypes.h"
#include "XMLThemeTypes.h"
#include <math.h>

AudioInfo *XMLSongBuilder::createAudioInfo(XMLNode xNode) {
   XMLNode xmlAudioInfo = xNode.getChildNode(AUDIO_INFO);
   
   if (xmlAudioInfo.isEmpty() ) {
      return NULL;
   }
   
   AudioInfo *ai = new AudioInfo();
   std::string strType( xmlAudioInfo.getAttribute(THEME_ATTR_TYPE));
   std::string strLength( xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_TRACK_LENGTH));   
   std::string strSongUnit (xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_UNIT));
   std::string strArtist ( ((xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_ARTIST) == NULL) ? "" : xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_ARTIST)) );
   std::string strTrack ( ((xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_TRACK) == NULL ) ? "" : xmlAudioInfo.getAttribute(AUDIO_INFO_ATTR_TRACK)) );
   std::string strBeatUnit;
   XMLNode xmlBeatSequence = xmlAudioInfo.getChildNode(AUDIO_INFO_BEAT_SEQUENCE);
   //todo refactor

 	  Mix_MusicType type = MUS_NONE;
    if (( strType == "mp3" ) || (strType == "MP3")) {
    	type = MUS_MP3;
    }
    if (( strType == "wav" ) || (strType == "WAV")) {
    	type = MUS_WAV;
    }
    ai->setType(type);

    ai->setArtist(strArtist);
    ai->setTrack(strTrack);

   if ( ! xmlBeatSequence.isEmpty() ) {
          	
      if ((strSongUnit == "seconds" ) || (strSongUnit == "s")) {
        ai->setSongLength( int(atof(strLength.c_str()) * 1000) );
      } else if ((strSongUnit == "milliseconds" ) || (strSongUnit == "ms" )) {
        ai->setSongLength( int(atof(strLength.c_str())) );
      }
      //todo parse minute formats

      strBeatUnit = xmlBeatSequence.getAttribute(AUDIO_INFO_ATTR_UNIT);
      XMLNode xmlBeat;
      int i = 0;
      do {
        xmlBeat = xmlBeatSequence.getChildNode(AUDIO_INFO_BEAT_SEQUENCE_BEAT, &i);
        if (! xmlBeat.isEmpty()) {
          std::string strBeatTime ( xmlBeat.getText() );
          if ((strBeatUnit == "seconds" ) || (strBeatUnit == "s")) {
            ai->addTiming( int(atof(strBeatTime.c_str()) * 1000) );
#ifdef DEBUG
            std::cout << "adding beat at " << int(atof(strBeatTime.c_str()) * 1000) << " milliseconds." << std::endl;
#endif
          } else if ((strBeatUnit == "milliseconds" ) || (strBeatUnit == "ms" )) {
            ai->addTiming( int(atof(strBeatTime.c_str())) );
#ifdef DEBUG
            std::cout << "adding beat at " << int(atof(strBeatTime.c_str())) << " milliseconds." << std::endl;
#endif
          }
          //todo parse Minute formats
        }
      } while (! xmlBeat.isEmpty());
   }
   if ( ! ai->prepare() ) {
      //not fit for consumption;
      delete ai;
      return NULL;
   }
   return ai;
}

MusicResource *XMLSongBuilder::createMusicResource(XMLNode xMainNode, std::string strThemeDir) {
    MusicResource *musicResource = NULL;
	 	XMLNode resourceRef;
	 	
	 	resourceRef = xMainNode.getChildNode(THEME_SONG_RESOURCE);	 	
	 	if (!resourceRef.isEmpty()) {
#ifdef DEBUG
      std::cout << THEME_SONG_RESOURCE << " element has been found." << std::endl;
#endif
      XMLNode trackName = resourceRef.getChildNode(SONG_TRACK_NAME);
      std::string strText(trackName.getText());
      strText = strThemeDir + "/" + strText;
      musicResource = new MusicResource(XMLSongBuilder::createAudioInfo(resourceRef), strText);
      musicResource->load();
    }
    return musicResource;  
}
