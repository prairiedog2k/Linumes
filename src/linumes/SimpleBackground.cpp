#include "framework/OpenGLHeaders.h"
#include "SimpleBackground.h"
#include "BoardTypes.h"
#include "framework/TextureResource.h"
#include "framework/ResourceHelper.h"



namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;


SimpleBackground::SimpleBackground() : HF::Rendered(true),  HF::Positioned(), HF::Themed(), _depth(-20.0f), _quad(), _texname(BOARD_BG)
{

}

SimpleBackground::SimpleBackground(std::string texname) : HF::Rendered(true),  HF::Positioned(), HF::Themed(), _depth(-20.0f), _quad(), _texname(texname)
{

}


SimpleBackground::SimpleBackground(float x, float y) : HF::Rendered(true),  HF::Positioned(x,y), _depth(-20.0f), _quad(), _texname(BOARD_BG)
{

}

SimpleBackground::SimpleBackground(float x, float y, std::string texname) : HF::Rendered(true),  HF::Positioned(x,y), _depth(-20.0f), _quad(), _texname(texname)
{

}

SimpleBackground::~SimpleBackground()
{

}
void  SimpleBackground::bindTexture() {
	HF::TextureResource * tr = HF::ResourceHelper::getTextureResource(getTheme(), _texname);
	if (nullptr == tr) {
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


} // namespace Hunchback::Linumes