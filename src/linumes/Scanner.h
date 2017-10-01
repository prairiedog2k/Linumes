#ifndef SCANNER_H_
#define SCANNER_H_

#include "framework/Rendered.h"
#include "framework/TimePositioned.h"
#include "framework/Themed.h"
#include "GL/gl.h"

class Scanner : public Rendered, public TimePositioned, public Themed
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

  float getBoardWidth() { return dimensionx * columns; };
  GLuint getTexture();
  GLuint getMask();  
  bool paused;
  
public:
	Scanner(float minx, float maxx, float posy, float ratex, float dimx, float dimy, int colcount);
	virtual ~Scanner();
	void update(unsigned int currTime);
	
	void togglePause();
	
	int getCurrentColumn() { return colpos; };
	bool isReset() { return reset; };
	virtual void setTheme(Theme *theme);	
	//override
	void Draw();
};

#endif /*SCANNER_H_*/
