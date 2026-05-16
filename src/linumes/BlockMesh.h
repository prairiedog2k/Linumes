#include "framework/OpenGLHeaders.h"
#pragma once

namespace Hunchback::Linumes {

class BlockMesh {
private:
	static bool isLoaded;
	static GLint listID;
	static GLint Gen3DObjectList();
public:
 	static GLint getListId();
};

} // namespace Hunchback::Linumes
