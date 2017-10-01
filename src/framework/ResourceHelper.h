#ifndef RESOURCEHELPER_H_
#define RESOURCEHELPER_H_

#include <iostream>

#include "BaseResource.h"
#include "TextureResource.h"
#include "AudioResource.h"
#include "FontResource.h"
#include "StringResource.h"
#include "MusicResource.h"
#include "PluginResource.h"
#include "Theme.h"

using namespace std;

class ResourceHelper
{
public:
  static TextureResource *getTextureResource( Theme * theme, const string resourceName );
  static AudioResource *getAudioResource( Theme * theme, const string resourceName );
  static MusicResource *getMusicResource( Theme * theme, const string resourceName );  
  static FontResource *getFontResource( Theme * theme, const string resourceName );
  static PluginResource *getPluginResource( Theme * theme, const string resourceName );
  static StringResource *getStringResource( Theme *theme, const string resourceName);
private:
  static bool isValid( Theme * theme, const string resourceName );
  static BaseResource *getBaseResource( Theme * theme, const string resourceName);
};

#endif /*RESOURCEHELPER_H_*/

