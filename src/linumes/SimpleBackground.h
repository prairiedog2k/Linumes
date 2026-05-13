#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "framework/Positioned.h"
#include "framework/Rendered.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class SimpleBackground : public HF::Rendered, public HF::Positioned, public HF::Themed
{
protected:
  float _depth;
  void bindTexture();
  HF::TextureQuad _quad;
  std::string _texname;
public:
	SimpleBackground();
	SimpleBackground(std::string texname);
	SimpleBackground(float x, float y);
	SimpleBackground(float x, float y, std::string texname);
	virtual ~SimpleBackground();
	void Draw();

	void setDepth (float depth) { _depth = depth; };
	float getDepth() { return _depth; };
};

} // namespace Hunchback::Linumes

#endif /*BACKGROUND_H_*/
