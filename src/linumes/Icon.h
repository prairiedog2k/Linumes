#ifndef ICON_H_
#define ICON_H_

#include "framework/Themed.h"
#include "framework/Timed.h"
#include "framework/Rendered.h"
#include "framework/Positioned.h"
#include "framework/TextureQuad.h"

class Icon : public Themed, public Timed, public Rendered, public Positioned
{
private:
 float _dimension;
 float _decay;
 float _currDimension;
 TextureQuad _quad;
public:
	Icon();
	virtual ~Icon();
	void Draw();
	void Pulse();
	void setDimension(float dimension) { _dimension = dimension; };
	void setDecay(float decay) { _decay = decay; };
protected:
	virtual GLuint getTexture(int which);
};

#endif /*ICON_H_*/
