#pragma once

#include <vector>
#include "framework/Timed.h"
#include "framework/Rendered.h"
#include "framework/Positioned.h"
#include "framework/Themed.h"
#include "framework/TextureQuad.h"
#include "framework/AudioManager.h"

namespace Hunchback::Linumes {
namespace HF = Hunchback::Framework;

class Grid : public HF::Timed, public HF::Rendered, public HF::Positioned, public HF::Themed
{
private:
	float dimension;
	int boardcolumns;
	int boardrows;
	bool hasMask;

	HF::TextureQuad _quad;
	HF::AudioManager *audioManager;

	unsigned int currTick;
	std::vector<float> lastLevel;
	std::vector<unsigned int> lastLevelTick;
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
	float getDimension() const { return dimension; };
	virtual void setTheme(HF::Theme *theme);
	void setAudioManager(HF::AudioManager *am) { audioManager = am; };
	void Draw();
	void update(unsigned int tick) { currTick = tick;};
};

} // namespace Hunchback::Linumes
