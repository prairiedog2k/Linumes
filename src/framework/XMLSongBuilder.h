#ifndef XMLSONGBUILDER_H
#define XMLSONGBUILDER_H


#include "xmlParser.h"
#include "AudioInfo.h"
#include "MusicResource.h"
#include <string>

using namespace std;

class XMLSongBuilder {
public:
   static AudioInfo *createAudioInfo(XMLNode xNode);
   static MusicResource *createMusicResource(XMLNode xMainNode, std::string strThemeDir);
};
#endif  //XMLSONGBUILDER_H
