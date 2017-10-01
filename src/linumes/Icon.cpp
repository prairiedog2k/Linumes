#include "Icon.h"
#include "BoardTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"

Icon::Icon() : Rendered(true), _quad()
{

}

Icon::~Icon()
{
}

GLuint Icon::getTexture(int which)
{
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), 
			std::string ( (which == 0 ? BOARD_ICON_MASK : BOARD_ICON) ) );
	if (NULL == tr) {
		return 0;
	}
	return tr->getResource();
}

void Icon::Draw() {
	if (isRenderable())
	{ 
		int currTime = SDL_GetTicks();
		if (! canMove(currTime) ) {
			_currDimension = _dimension + ((float)( (float)currTime / (float)( _initialTime + _wait )) * 0.10f);
		} else {
			_currDimension = _dimension;
		}

		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		glBindTexture( GL_TEXTURE_2D, getTexture(0));

		glTranslatef( (GLfloat)_x,(GLfloat)_y, -5.0f );

		glBlendFunc(GL_DST_COLOR,GL_ZERO);		
		_quad.setDimensionAndPosition2D(_currDimension/2.0f,_currDimension/2.0f,_currDimension);
		_quad.setZ(1.0f);
		_quad.Draw();

		glBindTexture( GL_TEXTURE_2D, getTexture(1));
		glBlendFunc(GL_ONE, GL_ONE);

		_quad.Draw();

		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

	}
}

void Icon::Pulse() {
	_initialTime = SDL_GetTicks();	
	_wait = 75;
}
