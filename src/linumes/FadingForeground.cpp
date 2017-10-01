#include "FadingForeground.h"
#include <math.h>
#include "BoardTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"

#define BASE_FONT_12 "base_font_12" 


FadingForeground::FadingForeground(float x, float y, unsigned int duration) : SimpleBackground(x,y), TimeLimited(duration), _fade(FADE_IN), _displayDuration(60000), _displayTimeBegin(0)
{
	setDepth(2.0f);
}

FadingForeground::~FadingForeground()
{

}
void FadingForeground::drawDisplayInfo() {
	unsigned int currTime = SDL_GetTicks();
	
	bool canShow = (currTime - _displayTimeBegin)  < _displayDuration; 
	if ( ( canShow ) && ( ! (_displayInfo == ""))) {
		Theme * theme = getTheme();
		if (NULL != theme) {
			Font *f1 = ResourceHelper::getFontResource(getTheme(),  BASE_FONT_12 )->getResource();
			if (NULL != f1) {
				f1->drawText(_displayInfo.c_str(), 5, 5, false);
			}
		}
	}
}

void FadingForeground::Draw() {
	if (isRenderable() ) {
		float alpha =  ::sinf( M_PI / 2 * getPercentComplete() );
		alpha *= alpha;
		alpha = ::sqrtf(alpha);
		alpha = 1 - alpha;
		alpha = _fade == FADE_IN ?  1- alpha : alpha;
		alpha = 0.5f + (alpha * 0.5f);
		
	    /* Blending Function For Translucency Based On Source Alpha Value  */
	    glEnable( GL_BLEND );
		glEnable( GL_DEPTH_TEST );
	    glBlendFunc( GL_ZERO, GL_SRC_ALPHA );

		glPushMatrix();
			glTranslatef( getX(), getY(), 0.0f );
			glColor4f(1.0f,1.0f,1.0f,alpha);
			glBegin( GL_QUADS );				
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glVertex3f( -13.3f, -10.0f,  getDepth() );
				glVertex3f(  13.3f, -10.0f,  getDepth() );
				glVertex3f(  13.3f,  10.0f,  getDepth() );
				glVertex3f( -13.3f,  10.0f,  getDepth() );
			glEnd();
		glPopMatrix();
		
	    glDisable( GL_BLEND );
	    glDisable( GL_DEPTH_TEST );
	    
	    drawDisplayInfo();
	}
}

