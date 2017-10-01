#include "Grid.h"
#include "BoardTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"

Grid::Grid() : Timed(), Rendered(true), Positioned(), Themed(), _quad(), audioManager(NULL)
{
}

Grid::Grid(float posx, float posy, float dim, int columns, int rows) : 
	Timed(), 
	Rendered(true), 
	Positioned(posx, posy), 
	Themed(), 
	dimension(dim),
	boardcolumns(columns),
	boardrows(rows),
	hasMask(false),
	_quad(),
	audioManager(NULL),
	currTick(0),
	decay(0.00002f)
	{
	lastLevel = new float[columns];
	lastLevelTick = new unsigned int[columns];
	}

Grid::~Grid()
{
	delete[] lastLevel;
	delete[] lastLevelTick;
}

void Grid::setTheme(Theme *theTheme) {
	Themed::setTheme(theTheme);
	hasMask = (NULL != ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_GRID_MASK)));
}

GLuint Grid::getMask() {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_GRID_MASK));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

GLuint Grid::getTexture() {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_GRID));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

GLuint Grid::getSideBarTexture(bool mask) {
	TextureResource *tr = ResourceHelper::getTextureResource(getTheme(), std::string ( mask ? BOARD_SIDEBAR_MASK : BOARD_SIDEBAR));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

GLuint Grid::getHeaderTexture(bool mask) {
	TextureResource *tr = ResourceHelper::getTextureResource(getTheme(), std::string ( mask ? BOARD_HEADER_MASK : BOARD_HEADER));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

GLuint Grid::getAudioLevelTexture(bool mask) {
	TextureResource *tr = ResourceHelper::getTextureResource(getTheme(), std::string ( mask ? BOARD_AUDIO_LEVEL_MASK : BOARD_AUDIO_LEVEL));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

void Grid::drawDecorations() {

	GLfloat y0 = getY() -( (boardrows * dimension) / 2.0f );
	GLfloat y1 = getY() + ( (boardrows * dimension) / 2.0f );

	glBindTexture( GL_TEXTURE_2D, getSideBarTexture(true) );		
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	GLfloat glx = ((GLfloat)getX()) - ( (boardcolumns * dimension) / 2.0f );
	GLfloat gly = ((GLfloat)getY());
	glPushMatrix();
	glTranslatef(glx,gly,-5.0f);

	glBegin(GL_QUADS);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( -dimension, y0, 1.0f );
	// Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(  0.0f, y0, 1.0f );
	// Top Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.00f );
	glVertex3f(  0.0f, y1 , 1.0f );
	// Top Left Of The Texture and Quad
	glTexCoord2f( 0.00f, 0.00f );
	glVertex3f( -dimension,  y1, 1.0f);
	glEnd();

	glBindTexture( GL_TEXTURE_2D, getSideBarTexture(false) );
	glBlendFunc(GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( -dimension, y0, 1.0f );
	// Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(  0.0f, y0, 1.0f );
	// Top Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.00f );
	glVertex3f(  0.0f, y1 , 1.0f );
	// Top Left Of The Texture and Quad
	glTexCoord2f( 0.00f, 0.00f );
	glVertex3f( -dimension,  y1, 1.0f);
	glEnd();

	glPopMatrix();

	y0 = getY() + ( (boardrows * dimension) / 2 );
	y1 = getY() + ( (boardrows * dimension) / 2 ) + (dimension/2.0f);

	glBindTexture( GL_TEXTURE_2D, getHeaderTexture(true) );		
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	glx = ((GLfloat)getX()) - ( (boardcolumns * dimension) / 2 );
	gly = ((GLfloat)getY());
	glPushMatrix();
	glTranslatef(glx,gly,-5.0f);

	glBegin(GL_QUADS);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0.0f, y0, 1.0f );
	// Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(  boardcolumns * dimension, y0, 1.0f );
	// Top Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.00f );
	glVertex3f(  boardcolumns * dimension, y1 , 1.0f );
	// Top Left Of The Texture and Quad
	glTexCoord2f( 0.00f, 0.00f );
	glVertex3f( 0.0,  y1, 1.0f);
	glEnd();

	glBindTexture( GL_TEXTURE_2D, getHeaderTexture(false) );
	glBlendFunc(GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	// Bottom Left Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0.0f, y0, 1.0f );
	// Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(  boardcolumns * dimension, y0, 1.0f );
	// Top Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.00f );
	glVertex3f(  boardcolumns * dimension, y1 , 1.0f );
	// Top Left Of The Texture and Quad
	glTexCoord2f( 0.00f, 0.00f );
	glVertex3f( 0.0,  y1, 1.0f);
	glEnd();
	glPopMatrix();

}

void Grid::drawAudioLevels() {
	if (NULL == audioManager) {
		return;
	}

	GLfloat cx1, cx2, cy1, cy2;
	GLfloat glx;
	GLfloat gly;

	cx1 = 0.0f;
	cx2 = dimension;
	cy1 = 0.0f;
	cy2 = dimension/3.0f;


	for (int i = 0; i < boardcolumns; i++) {

		float soundLevel = audioManager->getSoundLevel(i);
		if (lastLevel[i] < soundLevel) {
			lastLevel[i] = soundLevel;
			lastLevelTick[i] = currTick;
		} else {
			lastLevel[i] -= decay * (currTick - lastLevelTick[i]);
			soundLevel = lastLevel[i];
		}
		int level = (int) ( ((float) boardrows * 3) * soundLevel);
		for (int j = 0; j < level; j++) {
			glx = ((GLfloat)getX()) + (const float)i*dimension - ( (boardcolumns * dimension) / 2 );
			gly = ((GLfloat)getY()) + (const float)j*dimension/3.0f - ( (boardrows * dimension) / 2 );


			glPushMatrix();
			glTranslatef(glx,gly,-5.0f);
			/* Start Drawing Quads */
			//glColor4f (0.75f,0.75f,0.75f,0.5f);
			glColor4f (1.0f,1.0f,1.0f,1.0f);
			glNormal3f( 0.0f, 0.0f, 1.0f );

			glBindTexture( GL_TEXTURE_2D, getAudioLevelTexture(true) );
			glBlendFunc(GL_DST_COLOR,GL_ZERO);		
			_quad.Draw(cx1,cx2,cy1,cy2,1.0f);

			glBindTexture( GL_TEXTURE_2D, getAudioLevelTexture(false) );
			glBlendFunc(GL_ONE, GL_ONE);
			_quad.Draw(cx1,cx2,cy1,cy2,1.0f);

			glPopMatrix();
		}
	}	
}

void Grid::drawGrid() {

	GLfloat cx1, cx2, cy1, cy2;
	GLfloat glx;
	GLfloat gly;

	cx1 = 0.0f;
	cx2 = dimension;
	cy1 = 0.0f;
	cy2 = dimension;

	for (int i = 0; i < boardcolumns; i++) {
		for (int j = 0; j < boardrows; j++) {
			glx = ((GLfloat)getX()) + (const float)i*dimension - ( (boardcolumns * dimension) / 2 );
			gly = ((GLfloat)getY()) + (const float)j*dimension - ( (boardrows * dimension) / 2 );
			glPushMatrix();
			glTranslatef(glx,gly,-5.0f);
			/* Start Drawing Quads */
			glColor4f (1.0f,1.0f,1.0f,1.0f);

			glNormal3f( 0.0f, 0.0f, 1.0f );
			if (!hasMask) {
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );
				glBindTexture( GL_TEXTURE_2D, getTexture() );
				_quad.Draw(cx1,cx2,cy1,cy2,1.0f);
			} else {
				glBindTexture( GL_TEXTURE_2D, getMask() );
				glBlendFunc(GL_DST_COLOR,GL_ZERO);
				_quad.Draw(cx1,cx2,cy1,cy2,1.0f);
				glBindTexture( GL_TEXTURE_2D, getTexture());
				glBlendFunc(GL_ONE, GL_ONE);
				_quad.Draw(cx1,cx2,cy1,cy2,1.0f);
			}

			glPopMatrix();
		}
	}
}

void Grid::Draw() {
	if (isRenderable())
	{
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);		

		drawDecorations();
		drawAudioLevels();
		drawGrid();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}	
}
