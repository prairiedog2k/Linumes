#ifndef BLOCKMESH_H_
#define BLOCKMESH_H_

#include <GL/gl.h>

using namespace std;

class BlockMesh {
private:
	static bool isLoaded;
	static GLint listID;
	static GLint Gen3DObjectList();  
public:  
 	static GLint getListId();
};

#endif /*BLOCKMESH_H_*/
