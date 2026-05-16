#pragma once

#include "framework/Themed.h"
#include "framework/Timed.h"
#include "framework/Rendered.h"
#include "framework/Positioned.h"
#include "framework/TextureQuad.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class Icon : public HF::Themed, public HF::Timed, public HF::Rendered, public HF::Positioned
{
private:
 float _dimension;
 float _decay;
 float _currDimension;
 HF::TextureQuad _quad;
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

} // namespace Hunchback::Linumes
