#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "framework/Positioned.h"
#include "framework/Rendered.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"

class SimpleBackground : public Rendered, public Positioned, public Themed
{
protected:
  float _depth;
  void bindTexture();
  TextureQuad _quad;
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

#endif /*BACKGROUND_H_*/
