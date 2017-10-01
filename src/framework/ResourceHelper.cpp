#include "ResourceHelper.h"


TextureResource *ResourceHelper::getTextureResource( Theme * theme, const string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<TextureResource *>(br);
}

MusicResource *ResourceHelper::getMusicResource( Theme * theme, const string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<MusicResource *>(br);
}


AudioResource *ResourceHelper::getAudioResource( Theme * theme, const string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<AudioResource *>(br);
}

FontResource *ResourceHelper::getFontResource( Theme *theme, const string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<FontResource *>(br);
}

PluginResource *ResourceHelper::getPluginResource( Theme *theme, const string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<PluginResource *>(br);
}


StringResource *ResourceHelper::getStringResource( Theme *theme, const string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (NULL == br) {
		return NULL;
	}
	return dynamic_cast<StringResource *>(br);
}

bool ResourceHelper::isValid( Theme * theme, const string resourceName ) {
	return ((NULL != theme) && (resourceName.size() > 0));
}

BaseResource *ResourceHelper::getBaseResource( Theme *theme, const string resourceName) {
	if (!isValid(theme, resourceName)) {
		return NULL;
	}
	BaseResource * retVal = NULL;
	try {
		retVal = theme->getResource( resourceName ); 
		if ( ( NULL == retVal ) && ( NULL != theme->getBaseTheme() ) ) {
            retVal = theme->getBaseTheme()->getResource(resourceName);
        }
	} catch(...) {
		return NULL;
	}
	return retVal;
}
