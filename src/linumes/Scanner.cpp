
#include "Scanner.h"

#include "SDL.h"
#include <iostream>
#include "BoardTypes.h"
#include "framework/ResourceHelper.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>


Scanner::Scanner( float minx,
		float maxx, 
		float posy, 
		float ratex, 
		float dimx, 
		float dimy,
		int colcount) : Rendered(true), 
		TimePositioned(minx, posy, ratex, 0.0f, 0,0,false),
		minimumx(minx),
		maximumx(maxx),
		dimensionx(dimx),
		dimensiony(dimy),
		columns(colcount) ,
		colpos(0),																		
		reset(true),
		hasMask(false)
		{
	paused = false; 	
		}

Scanner::~Scanner()
{
#ifdef DEBUG
	std::cout << "Scanner Deleted" << endl;
#endif
}

void Scanner::setTheme(Theme *theTheme) {
	Themed::setTheme(theTheme);
	hasMask = (NULL != ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_FLAG_MASK)));
}

GLuint Scanner::getMask() {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_FLAG_MASK));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

GLuint Scanner::getTexture() {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string (BOARD_FLAG));
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

void Scanner::Draw() {
	static GLfloat yrot = 0;
	yrot += 0.01f;
	if (isRenderable())
	{
		glLoadIdentity();

		glEnable(GL_BLEND);

		glBlendFunc( GL_SRC_ALPHA, GL_ONE );

		glDisable(GL_DEPTH_TEST);

		glTranslatef(0.0f, 0.0f,-5.000f);

		glColor3f(0.5f,0.5f,0.5f);    

		glBegin(GL_QUADS);
		// tracer behind
		// Bottom Left Of The Texture and Quad
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( max(minimumx, getX() - dimensionx), getY() - dimensiony, 1.0f );
		// Bottom Right Of The Texture and Quad
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(  getX(), getY() - dimensiony, 1.0f );
		// Top Right Of The Texture and Quad
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(  getX(), getY() , 1.0f );
		// Top Left Of The Texture and Quad
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( max(minimumx, getX() - dimensionx),  getY(), 1.0f );

		//solid bar in front	    
		// Bottom Left Of The Texture and Quad
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( getX(), getY() - dimensiony, 1.0f );	    
		// Bottom Right Of The Texture and Quad
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(  getX()+0.002, getY() - dimensiony, 1.0f );
		// Top Right Of The Texture and Quad
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(  getX()+0.002, getY() , 1.0f );
		// Top Left Of The Texture and Quad
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( getX(),  getY(), 1.0f );	    
		glEnd();

		glEnable(GL_TEXTURE_2D);

		if (!hasMask) {    
			glBindTexture( GL_TEXTURE_2D, getTexture() );
		} else {
			glBindTexture( GL_TEXTURE_2D, getMask() );
			glBlendFunc(GL_DST_COLOR,GL_ZERO);		
		}

		glBegin( GL_QUADS );
		/* Front Face */
		/* Normal Pointing Towards Viewer */
		glNormal3f( 0.0f, 0.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f ); 
		glVertex3f( getX(), getY(),  1.0f );
		/* Point 2 (Front) */
		glTexCoord2f( 1.0f, 1.0f ); 
		glVertex3f( getX() + dimensionx, getY(),  1.0f );
		/* Point 3 (Front) */
		glTexCoord2f( 1.0f, 0.0f ); 
		glVertex3f( getX() + dimensionx, getY() + dimensionx / 2 ,  1.0f );
		/* Point 4 (Front) */
		glTexCoord2f( 0.0f, 0.0f ); 
		glVertex3f( getX(), getY() + dimensionx / 2,  1.0f );        
		glEnd();

		if (hasMask) {
			glBindTexture( GL_TEXTURE_2D, getTexture());
			glBlendFunc(GL_ONE, GL_ONE);
			glBegin( GL_QUADS );
			/* Front Face */
			/* Normal Pointing Towards Viewer */
			glNormal3f( 0.0f, 0.0f, 1.0f );
			glTexCoord2f( 0.0f, 1.0f ); 
			glVertex3f( getX(), getY(),  1.0f );
			/* Point 2 (Front) */
			glTexCoord2f( 1.0f, 1.0f ); 
			glVertex3f( getX() + dimensionx, getY(),  1.0f );
			/* Point 3 (Front) */
			glTexCoord2f( 1.0f, 0.0f ); 
			glVertex3f( getX() + dimensionx, getY() + dimensionx / 2 ,  1.0f );
			/* Point 4 (Front) */
			glTexCoord2f( 0.0f, 0.0f ); 
			glVertex3f( getX(), getY() + dimensionx / 2,  1.0f );        
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
}

void Scanner::update(unsigned int currTime) {
	float currX = this->forecastX(currTime);
	if (currX > maximumx) {
		this->setX(minimumx);
		reset = true;
	} else {
		this->setX(currX);
		reset = false;
	}
	colpos = (int) ((( (currX - minimumx) / (maximumx - minimumx) ) * columns));
}


void Scanner::togglePause() {
	paused = !paused;
	if (paused) {
		this->setStopped(true);
	} else {
		this->setInitialTime( SDL_GetTicks() );
		this->setWait(0);
		this->setStopped( false );
	}
}
