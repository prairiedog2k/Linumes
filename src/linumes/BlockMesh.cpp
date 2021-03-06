#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "BlockMesh.h"


bool BlockMesh::isLoaded = false;

GLint BlockMesh::listID=-1;

// 30 Verticies
// 15 Texture Coordinates
// 51 Normals
// 56 Triangles

static unsigned char face_indicies[56][9] = {
// Pyramid01
	{0,1,2 ,0,1,2 ,0,1,2 }, {0,2,3 ,3,3,4 ,0,1,2 }, {0,3,4 ,5,5,6 ,0,1,2 },
	{0,4,1 ,7,7,7 ,0,1,2 }, {1,5,6 ,1,8,9 ,1,3,4 }, {1,6,2 ,1,9,2 ,1,4,2 },
	{2,6,7 ,10,10,11 ,1,3,4 }, {2,7,3 ,12,11,4 ,1,4,2 }, {3,7,8 ,13,13,14 ,1,3,4 },
	{3,8,4 ,15,14,6 ,1,4,2 }, {4,8,5 ,16,16,16 ,1,3,4 }, {4,5,1 ,16,16,16 ,1,4,2 },
	{5,9,10 ,17,17,17 ,3,5,6 }, {5,10,6 ,8,18,9 ,3,6,4 }, {6,10,11 ,19,19,19 ,3,5,6 },
	{6,11,7 ,20,20,11 ,3,6,4 }, {7,11,12 ,21,21,21 ,3,5,6 }, {7,12,8 ,22,22,14 ,3,6,4 },
	{8,12,9 ,23,23,23 ,3,5,6 }, {8,9,5 ,24,24,24 ,3,6,4 }, {9,13,10 ,25,26,25 ,7,8,9 },
	{10,13,11 ,27,26,27 ,10,11,9 }, {11,13,12 ,28,26,28 ,9,11,7 },
	{12,13,9 ,29,26,29 ,7,11,12 }, {15,14,9 ,30,30,30 ,13,14,13 },
	{10,9,14 ,30,30,30 ,14,13,14 }, {14,16,10 ,31,32,33 ,12,7,12 },
	{11,10,16 ,33,33,32 ,7,12,7 }, {16,17,11 ,32,34,35 ,9,7,9 },
	{12,11,17 ,35,35,34 ,7,9,7 }, {17,15,12 ,36,36,36 ,7,12,7 },
	{9,12,15 ,36,36,36 ,12,7,12 }, {19,18,15 ,37,38,39 ,13,14,13 },
	{14,15,18 ,31,39,38 ,14,13,14 }, {18,20,14 ,38,38,31 ,12,7,12 },
	{16,14,20 ,32,31,38 ,7,12,7 }, {20,21,16 ,38,37,32 ,9,7,9 },
	{17,16,21 ,34,32,37 ,7,9,7 }, {21,19,17 ,40,40,40 ,7,12,7 },
	{15,17,19 ,40,40,40 ,12,7,12 }, {23,22,19 ,39,41,37 ,13,14,13 },
	{18,19,22 ,38,37,41 ,14,13,14 }, {22,24,18 ,41,42,38 ,12,7,12 },
	{20,18,24 ,38,38,42 ,7,12,7 }, {24,25,20 ,42,43,38 ,9,7,9 },
	{21,20,25 ,37,38,43 ,7,9,7 }, {25,23,21 ,40,40,40 ,7,12,7 },
	{19,21,23 ,40,40,40 ,12,7,12 }, {27,26,23 ,44,44,44 ,13,14,13 },
	{22,23,26 ,41,44,44 ,14,13,14 }, {26,28,22 ,45,46,41 ,12,7,12 },
	{24,22,28 ,42,41,46 ,7,12,7 }, {28,29,24 ,47,47,42 ,9,7,9 },
	{25,24,29 ,43,42,47 ,7,9,7 }, {29,27,25 ,48,49,49 ,7,12,7 },
	{23,25,27 ,50,49,49 ,12,7,12 }
};
static GLfloat vertices [30][3] = {
{-0.00134467f,-1.84311e-08f,0.051733f},{-0.08907f,-0.165014f,-0.0143404f},{0.16367f,-0.0877254f,-0.0143404f},
{0.0863807f,0.165014f,-0.0143404f},{-0.166359f,0.0877253f,-0.0143404f},{-0.222783f,-0.416241f,-0.0495737f},
{0.41474f,-0.221283f,-0.0495737f},{0.219783f,0.416241f,-0.0495737f},{-0.417741f,0.221283f,-0.0495737f},
{-0.397785f,-0.39644f,0.0180377f},{0.395095f,-0.39644f,0.0180377f},{0.395095f,0.39644f,0.0180377f},
{-0.397785f,0.39644f,0.0180377f},{-0.00134468f,-1.5123e-08f,-0.0124091f},{0.395095f,-0.39644f,0.0176413f},
{-0.397785f,-0.39644f,0.0176413f},{0.395095f,0.39644f,0.0176413f},{-0.397785f,0.39644f,0.0176413f},
{0.395492f,-0.39644f,0.0176413f},{-0.397388f,-0.39644f,0.0176413f},{0.395492f,0.39644f,0.0176413f},
{-0.397388f,0.39644f,0.0176413f},{0.395888f,-0.39644f,0.0176413f},{-0.396992f,-0.39644f,0.0176413f},
{0.395888f,0.39644f,0.0176413f},{-0.396992f,0.39644f,0.0176413f},{0.5f,-0.5f,-0.051733f},
{-0.5f,-0.5f,-0.051733f},{0.5f,0.5f,-0.0517329f},{-0.5f,0.5f,-0.0517329f}
};
static GLfloat normals [51][3] = {
{0.130782f,-0.427664f,0.894427f},{0.0779599f,-0.254933f,0.963811f},{0.091582f,-0.299478f,0.949697f},
{0.427664f,0.130782f,0.894427f},{0.299518f,0.0915941f,0.949684f},{-0.130782f,0.427664f,0.894427f},
{-0.0915713f,0.299444f,0.949709f},{-0.427664f,-0.130782f,0.894427f},{-0.0324675f,0.106171f,0.993818f},
{-0.0041013f,0.0134115f,0.999902f},{0.16508f,0.0504822f,0.984987f},{-0.0132853f,-0.00406272f,0.999904f},
{0.16508f,0.0504822f,0.984987f},{-0.0504349f,0.164925f,0.985016f},{0.00413529f,-0.0135226f,0.9999f},
{-0.0504349f,0.164925f,0.985016f},{-0.164843f,-0.0504099f,0.985031f},{0.0f,0.959692f,-0.281053f},
{-0.112779f,0.368794f,0.922644f},{-0.960285f,0.0f,-0.279021f},{-0.368594f,-0.112718f,0.922732f},
{0.0f,-0.959692f,-0.281053f},{0.112833f,-0.36897f,0.922567f},{0.959096f,0.0f,-0.283082f},
{0.36917f,0.112894f,0.922479f},{0.0f,-0.076575f,-0.997064f},{0.0f,-1.86813e-09f,-1.0f},
{0.076575f,0.0f,-0.997064f},{0.0f,0.076575f,-0.997064f},{-0.076575f,0.0f,-0.997064f},
{0.0f,-1.0f,0.0f},{0.534522f,0.267261f,0.801784f},{0.685994f,0.514496f,0.514496f},
{1.0f,0.0f,0.0f},{0.301511f,0.904534f,0.301511f},{0.0f,1.0f,0.0f},
{-1.0f,0.0f,0.0f},{0.57735f,0.57735f,0.57735f},{0.408248f,0.408248f,0.816497f},
{0.57735f,0.57735f,0.57735f},{0.0f,0.0f,-1.0f},{0.48004f,0.222871f,0.848464f},
{0.255341f,0.347095f,0.9024f},{0.46437f,0.593594f,0.657272f},{0.0f,-0.556555f,0.830811f},
{0.554514f,-3.14624e-08f,0.832174f},{0.554514f,-1.57312e-08f,0.832175f},{0.0f,0.556555f,0.830811f},
{-0.558608f,-3.13587e-08f,0.829432f},{-0.558608f,-1.56794e-08f,0.829432f},{-0.558608f,0.0f,0.829432f}
};

static GLfloat textures [15][2] = {
{0.5f,1.0f},{0.333333f,0.666667f},{0.666667f,0.666667f},
{0.166667f,0.333333f},{0.833333f,0.333333f},{0.0f,5.96046e-08f},
{1.0f,5.96046e-08f},{0.0f,1.0f},{0.5f,0.5f},
{1.0f,1.0f},{1.0f,2.0f},{0.5f,1.5f},
{0.0f,2.0f},{0.0f,0.0f},{1.0f,0.0f}
};

GLint BlockMesh::Gen3DObjectList()
{
 unsigned int i;
 unsigned int j;

 GLint lid=glGenLists(1);
   glNewList(lid, GL_COMPILE);
    glBegin (GL_TRIANGLES);
      for(i=0;i<sizeof(face_indicies)/sizeof(face_indicies[0]);i++)
       {
       for(j=0;j<3;j++)
        {
          int vi=face_indicies[i][j];
          int ni=face_indicies[i][j+3];//Normal index
          int ti=face_indicies[i][j+6];//Texture index
          glNormal3f (normals[ni][0],normals[ni][1],normals[ni][2]);
          glTexCoord2f(textures[ti][0],textures[ti][1]);
          glVertex3f (vertices[vi][0],vertices[vi][1],vertices[vi][2]);
        }
       }
    glEnd ();

   glEndList();
   return lid;
};

GLint BlockMesh::getListId() {
	if (! BlockMesh::isLoaded)  {
		BlockMesh::listID = BlockMesh::Gen3DObjectList();
		BlockMesh::isLoaded = true;
	}		
	return BlockMesh::listID;	
}



