#include "framework/OpenGLHeaders.h"
#ifndef SCANNER_H_
#define SCANNER_H_

#include "framework/Rendered.h"
#include "framework/TimePositioned.h"
#include "framework/Themed.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class Scanner : public HF::Rendered, public HF::TimePositioned, public HF::Themed
{
private:
  float minimumx;
  float maximumx;
  float dimensionx;
  float dimensiony;
  int columns;
  int colpos;
  bool reset;

  bool hasMask;

  float getBoardWidth() const { return dimensionx * columns; };
  GLuint getTexture();
  GLuint getMask();
  bool paused;

public:
	Scanner(float minx, float maxx, float posy, float ratex, float dimx, float dimy, int colcount);
	virtual ~Scanner();
	void update(unsigned int currTime);

	void togglePause();

	int getCurrentColumn() const { return colpos; };
	bool isReset()         const { return reset; };
	virtual void setTheme(HF::Theme *theme);
	//override
	void Draw();
};

} // namespace Hunchback::Linumes

#endif /*SCANNER_H_*/
