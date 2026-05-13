#ifndef XMLSONGBUILDER_H
#define XMLSONGBUILDER_H

#include <yaml-cpp/yaml.h>
#include "AudioInfo.h"
#include "MusicResource.h"
#include <string>

using namespace std;

class XMLSongBuilder {
public:
   static AudioInfo *createAudioInfo(const YAML::Node& themeNode);
   static MusicResource *createMusicResource(const YAML::Node& themeNode, std::string strThemeDir);
};
#endif  //XMLSONGBUILDER_H
