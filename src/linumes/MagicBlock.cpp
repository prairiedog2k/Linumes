#include "MagicBlock.h"
#include "BoardTypes.h"
#include "framework/ResourceHelper.h"
#include <math.h>

MagicBlock::MagicBlock(float x, float y, float dim, int boardpos) : Rendered(true), Themed(), TimeLimited(500), _state(NONE), _quad()
{
	_renderable = true;
	_x = x;
	_y = y;
	_dim = dim;
	_boardpos = boardpos;
}

MagicBlock::MagicBlock() : Rendered(true), Themed(), TimeLimited(500), _state(NONE), _quad()
{
	_renderable = false;
	_x = 0.0f;
	_y = 0.0f;
	_dim = 0.0f;
	_boardpos = 0;
}

MagicBlock::~MagicBlock()
{
}

void MagicBlock::setTheme(Theme *theTheme) {
	Themed::setTheme(theTheme);
}

GLuint MagicBlock::getNamedTexture(const char * arg) {
	TextureResource * tr = ResourceHelper::getTextureResource(getTheme(), std::string(arg));
	if (NULL == tr) {
		return 0;
	} else {
		return tr->getResource();
	}
}

GLuint MagicBlock::getTexture() {
	return getNamedTexture( BOARD_MAGICBOX); 
}


GLuint MagicBlock::getMask() {
	return getNamedTexture ( BOARD_MAGICBOX_MASK);
}

GLuint MagicBlock::getSparkTexture() {
	return getNamedTexture(BOARD_SPARK);	
}

GLuint MagicBlock::getSparkMask() {
	return getNamedTexture(BOARD_SPARK_MASK);
}

GLuint MagicBlock::getStarTexture() {
	return getNamedTexture(BOARD_STAR);	
}

GLuint MagicBlock::getStarMask() {
	return getNamedTexture(BOARD_STAR_MASK);
}


void MagicBlock::drawShrinker() {
	glLoadIdentity();

	glTranslatef( (GLfloat)_x,(GLfloat) _y , -4.95f );
	glRotatef(90.0f * getPercentComplete(), 0.0f,0.0f,1.0f);		
    
	glBindTexture( GL_TEXTURE_2D, getMask() );
	glBlendFunc(GL_DST_COLOR,GL_ZERO);		

	float scalefactor = (1.0f - getPercentComplete()) * _dim;
	
	_quad.setZ(1.0 + scalefactor);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();
	
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture( GL_TEXTURE_2D, getTexture());

	_quad.setZ(1.0 + scalefactor);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();

}

void MagicBlock::drawLooper() {
	glLoadIdentity();

	glTranslatef( (GLfloat)_x,(GLfloat) _y , -4.95f );
	glRotatef(90.0f * getPercentComplete(), 0.0f,0.0f,1.0f);		
    
	glBindTexture( GL_TEXTURE_2D, getMask() );
	glBlendFunc(GL_DST_COLOR,GL_ZERO);		

	float scalefactor = (1.0f - getPercentComplete());
	scalefactor = 1.0f - (scalefactor * 2.0f);
	if (scalefactor < 0.0f) {
		scalefactor *= -1;
	}
	scalefactor *= _dim *0.25f;
	
	_quad.setZ(1.0);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();
	
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture( GL_TEXTURE_2D, getTexture());

	_quad.setZ(1.0);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();

}

void MagicBlock::drawSpark() {
	glLoadIdentity();

	glTranslatef( (GLfloat)_x ,(GLfloat) _y , -4.94f );

	int side = (int)(4.0f * getPercentComplete());
	float sideComplete = (4.0f * getPercentComplete()) - ((float)side);
	float currx = 0.0f;
	float curry = 0.0f;
	if (side == 0) {
		currx = -_dim;
		curry = -_dim + (2 * sideComplete * _dim);
	} else if (side == 1) {
		currx = -_dim + (2 * sideComplete * _dim);
		curry = _dim;
	} else if (side == 2) {
		currx = _dim;
		curry = _dim - (2 * sideComplete *_dim);
	} else if (side == 3) {
		currx = _dim - (2 * sideComplete *_dim);
		curry = -_dim;
	}
	float scale = _dim * 0.35f;

	glBindTexture( GL_TEXTURE_2D, getSparkMask() );
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	_quad.Draw(currx - scale, currx + scale, curry-scale,curry+scale,1.0f);

	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture( GL_TEXTURE_2D, getSparkTexture());

	_quad.Draw(currx - scale, currx + scale, curry-scale,curry+scale,1.0f);
}

void MagicBlock::drawStar() {
	glLoadIdentity();

	glTranslatef( (GLfloat)_x,(GLfloat) _y , -4.95f );
	glRotatef(-90.0f * getPercentComplete(), 0.0f,0.0f,1.0f);		

	glBindTexture( GL_TEXTURE_2D, getStarMask() );
	glBlendFunc(GL_DST_COLOR,GL_ZERO);		

	float scalefactor = getPercentComplete() * _dim;

	_quad.setZ(1.0 + scalefactor);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();

	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture( GL_TEXTURE_2D, getStarTexture());

	_quad.setZ(1.0 + scalefactor);
	_quad.setDimensionAndPosition2D( 0.0f, 0.0f, 2.0f * (_dim + scalefactor) ) ;
	_quad.Draw();
}


void MagicBlock::Draw() {
	if (isRenderable() && ! isComplete()) {
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);    
		glDisable(GL_DEPTH_TEST);

		switch (_state) {
		case NONE:
			break;
		case SHRINKER:
			drawShrinker();
			break;
		case SPARK:
			drawSpark();
			break;
		case STAR:
			drawStar();
			break;
		case LOOPER:
			drawLooper();
			break;
		default: 
			break;
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}
