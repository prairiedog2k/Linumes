#ifndef GRID_H_
#define GRID_H_

#include "framework/Timed.h"
#include "framework/Rendered.h"
#include "framework/Positioned.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"
#include "framework/AudioManager.h"

class Grid : public Timed, public Rendered, public Positioned, public Themed
{
private:
	float dimension;
	int boardcolumns;
	int boardrows;	
	bool hasMask;
	
	TextureQuad _quad;
	AudioManager *audioManager;

	unsigned int currTick;
	float *lastLevel;
	unsigned int *lastLevelTick;
	float decay;
	
	GLuint getTexture();
	GLuint getMask();
	GLuint getSideBarTexture(bool mask);
	GLuint getHeaderTexture(bool mask);
	GLuint getAudioLevelTexture(bool mask); 

	void drawDecorations();
	void drawAudioLevels();
	void drawGrid();
public:
	Grid();
	Grid(float posx, float posy, float dim, int columns, int rows);
	virtual ~Grid();
	void setDimension( float dim) { dimension = dim; };
	float getDimension() { return dimension; };
	virtual void setTheme(Theme *theme);
	void setAudioManager(AudioManager *am) { audioManager = am; };
	void Draw();
	void update(unsigned int tick) { currTick = tick;};
};

#endif /*GRID_H_*/
