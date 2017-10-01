#include "XMLTheme.h"
#include "XMLThemeTypes.h"
#include "xmlParser.h"
#include "AudioResource.h"
#include "MusicResource.h"
#include "TextureResource.h"
#include "StringResource.h"
#include "FontResource.h"
#include "PluginResource.h"
#include "FontInfo.h"
#include "FontInfoBuilder.h"
#include "XMLSongBuilder.h"
#include "XMLSongTypes.h"
#include <string>
#include <cstdlib>
#include "SDL.h"

#include "XMLUtils.h"

XMLTheme::XMLTheme() : Theme(std::string("")), _resourcedir(std::string("")){
}

XMLTheme::XMLTheme(std::string resourcefile): Theme(resourcefile) {

}

XMLTheme::XMLTheme(std::string resourcefile, std::string resourcedir) : Theme(resourcefile), _resourcedir(resourcedir) {
	
}

bool XMLTheme::loadResourcesFromNode (XMLNode xMainNode) {
    bool bRetVal = false;
	if (! xMainNode.isEmpty()) {
		XMLNode xNode=xMainNode.getChildNode(THEME_DIR);

		themedir = xNode.getAttribute(THEME_ATTR_NAME);

		if (_resourcedir != "") {
			themedir = _resourcedir + "/" + themedir;
		}

		XMLNode resourceRef;
		int i = 0;
		resourceRef = xMainNode.getChildNode(THEME_SONG_RESOURCE);
		if (!resourceRef.isEmpty()) {
			resourceCount++;
			std::string strName(resourceRef.getAttribute(THEME_ATTR_NAME));
			MusicResource *musicResource = XMLSongBuilder::createMusicResource(xMainNode,themedir);
			if ((musicResource != NULL) && (strName.size() > 0)) {
				resources[strName]= musicResource;
			}
		}
		do {
			resourceRef = xMainNode.getChildNode(THEME_RESOURCE, &i);
			if (! resourceRef.isEmpty() ) {
				std::string strType( resourceRef.getAttribute(THEME_ATTR_TYPE));
				std::string strName(resourceRef.getAttribute(THEME_ATTR_NAME));

				//allow overrides to load resources outside of the the specified resource directory
				std::string strAltDir = nodeAttributeAsString(resourceRef, THEME_ATTR_ALTDIR);

				std::string strText = resourceRef.getText();

				if (strAltDir.size() > 0) {
					strText = strAltDir + "/" + strText;
				} else {
					strText = themedir + "/" + strText;
				}

				if (strType.compare(RESOURCE_AUDIO) == 0) {
					resourceCount++;
					AudioResource *ar = new AudioResource(NULL, strText);
					ar->load();
					resources[strName]= ar;
				}
				if (strType.compare(RESOURCE_TEXTURE) == 0) {
					resourceCount++;
					TextureResource *tr = new TextureResource(NULL,strText);
					tr->load();
					resources[strName] = tr;
				}
				if (strType.compare(RESOURCE_FONT) == 0) {
					resourceCount++;
					FontInfo fi = FontInfoBuilder::createFontInfo(resourceRef);
					FontResource *fr = new FontResource(&fi, strText);
					fr->load();
					resources[strName] = fr;
				}
				if (strType.compare(RESOURCE_PLUGIN) == 0) {
					resourceCount++;
					PluginResource *pr = new PluginResource(NULL, strText);
					pr->load();
					resources[strName] = pr;
				}
				if (strType.compare(RESOURCE_STRING) == 0) {
					resourceCount++;
					StringResource *sr = new StringResource(strText);
					sr->load();
					resources[strName] = sr;
				}

				if (strType.compare(RESOURCE_MESH) == 0) {
				}
			}
		} while ( ! resourceRef.isEmpty() );
		bRetVal = true;
	}
	return bRetVal;
}

bool XMLTheme::loadResources() {		
	if (_resourcedir != "") {
		themefile = _resourcedir + "/" + themefile;
	}
	
	XMLNode xMainNode=XMLNode::openFileHelper(themefile.c_str(),THEME_MAIN);
	return loadResourcesFromNode( xMainNode );
}

bool XMLTheme::init() {
	return loadResources();
}

void XMLTheme::release() {
	Theme::release();
}
