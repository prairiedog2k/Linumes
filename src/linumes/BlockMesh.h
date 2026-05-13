#include "framework/OpenGLHeaders.h"
#ifndef BLOCKMESH_H_
#define BLOCKMESH_H_

namespace Linumes {

class BlockMesh {
private:
	static bool isLoaded;
	static GLint listID;
	static GLint Gen3DObjectList();
public:
 	static GLint getListId();
};

} // namespace Linumes

#endif /*BLOCKMESH_H_*/
