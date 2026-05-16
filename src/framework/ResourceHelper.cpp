#include "ResourceHelper.h"

namespace Hunchback::Framework {

TextureResource *ResourceHelper::getTextureResource( Theme * theme, const std::string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<TextureResource *>(br);
}

MusicResource *ResourceHelper::getMusicResource( Theme * theme, const std::string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<MusicResource *>(br);
}


AudioResource *ResourceHelper::getAudioResource( Theme * theme, const std::string resourceName ) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<AudioResource *>(br);
}

FontResource *ResourceHelper::getFontResource( Theme *theme, const std::string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<FontResource *>(br);
}

PluginResource *ResourceHelper::getPluginResource( Theme *theme, const std::string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<PluginResource *>(br);
}


StringResource *ResourceHelper::getStringResource( Theme *theme, const std::string resourceName) {
	BaseResource *br = getBaseResource( theme, resourceName );
	if (nullptr == br) {
		return nullptr;
	}
	return dynamic_cast<StringResource *>(br);
}

bool ResourceHelper::isValid( Theme * theme, const std::string resourceName ) {
	return ((nullptr != theme) && (resourceName.size() > 0));
}

BaseResource *ResourceHelper::getBaseResource( Theme *theme, const std::string resourceName) {
	if (!isValid(theme, resourceName)) {
		return nullptr;
	}
	BaseResource * retVal = nullptr;
	try {
		retVal = theme->getResource( resourceName );
		if ( ( nullptr == retVal ) && ( nullptr != theme->getBaseTheme() ) ) {
            retVal = theme->getBaseTheme()->getResource(resourceName);
        }
	} catch(...) {
		return nullptr;
	}
	return retVal;
}

} // namespace Hunchback::Framework
