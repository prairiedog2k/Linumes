#include "SimpleBackground.h"
#include "BoardTypes.h"
#include "GL/gl.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"


SimpleBackground::SimpleBackground() : Rendered(true),  Positioned(), Themed(), _depth(-20.0f), _quad(), _texname(BOARD_BG)
{

}

SimpleBackground::SimpleBackground(std::string texname) : Rendered(true),  Positioned(), Themed(), _depth(-20.0f), _quad(), _texname(texname)
{

}


SimpleBackground::SimpleBackground(float x, float y) : Rendered(true),  Positioned(x,y), _depth(-20.0f), _quad(), _texname(BOARD_BG)
{

}

SimpleBackground::SimpleBackground(float x, float y, std::string texname) : Rendered(true),  Positioned(x,y), _depth(-20.0f), _quad(), _texname(texname)
{

}

SimpleBackground::~SimpleBackground()
{

}
void  SimpleBackground::bindTexture() {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), _texname);
	if (NULL == tr) {
		return;
	}
	glBindTexture( GL_TEXTURE_2D, tr->getResource() );
}

void SimpleBackground::Draw() {
	if (isRenderable() ) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPushMatrix();
			glTranslatef( getX(), getY(), getDepth() );
	
			bindTexture();
			
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			
			glNormal3f( 0.0f, 0.0f, 1.0f);

			_quad.Draw(-13.3f,13.3f,-10.0f,10.0f,10.0f);
			
		glPopMatrix();		
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}
