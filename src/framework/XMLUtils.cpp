#include "XMLUtils.h"

#include "XMLThemeTypes.h"
#include "AudioResource.h"
#include "MusicResource.h"
#include "TextureResource.h"
#include "StringResource.h"
#include "FontResource.h"
#include "PluginResource.h"
#include "FontInfo.h"
#include "FontInfoBuilder.h"

bool nodeHasAttribute(XMLNode resourceRef, const char * attr) {
	return (NULL == resourceRef.getAttribute(attr));
}

std::string nodeAttributeAsString(XMLNode resourceRef, const char *attr) {
	std::string retVal( ( nodeHasAttribute(resourceRef, attr) ? "" :  resourceRef.getAttribute(attr) ) );
	return retVal;
}

bool nodeAttributeAsBool(XMLNode node, const char *attributeName) {
	std::string strBoolean = node.getAttribute(attributeName) == NULL ? "false" : node.getAttribute(attributeName);
	return (strBoolean == "true");
}


//callers should be aware that they need to delete the resources returned by this function
BaseResource *createResourceFromNode(XMLNode resourceRef, std::string themedir) {
    if ( resourceRef.isEmpty() ) {
        return NULL;
    }
    BaseResource *br = NULL;
	std::string strType( resourceRef.getAttribute(THEME_ATTR_TYPE));
	std::string strName( resourceRef.getAttribute(THEME_ATTR_NAME));

	//allow overrides to load resources outside of the the specified resource directory
	std::string strAltDir = nodeAttributeAsString(resourceRef, THEME_ATTR_ALTDIR);

	std::string strText = resourceRef.getText();

	if (strAltDir.size() > 0) {
		strText = strAltDir + "/" + strText;
	} else {
		strText = themedir + "/" + strText;
	}

	if (strType.compare(RESOURCE_AUDIO) == 0) {
		AudioResource *ar = new AudioResource(NULL, strText);
		ar->load();
        br = ar;
	}
	if (strType.compare(RESOURCE_TEXTURE) == 0) {
		TextureResource *tr = new TextureResource(NULL,strText);
		tr->load();
        br = tr;
	}
	if (strType.compare(RESOURCE_FONT) == 0) {
		FontInfo fi = FontInfoBuilder::createFontInfo(resourceRef);
		FontResource *fr = new FontResource(&fi, strText);
		fr->load();
		br = fr;
	}
	if (strType.compare(RESOURCE_PLUGIN) == 0) {
		PluginResource *pr = new PluginResource(NULL, strText);
		pr->load();
		br = pr;
	}
	if (strType.compare(RESOURCE_STRING) == 0) {
		StringResource *sr = new StringResource(strText);
		sr->load();
		br = sr;
	}
	if (strType.compare(RESOURCE_MESH) == 0) {
		br = NULL;
	}
	return br;
}
