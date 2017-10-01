#ifndef MAGICBLOCK_H_
#define MAGICBLOCK_H_

#include "framework/Rendered.h"
#include "framework/Themed.h"
#include "framework/TimeLimited.h"
#include "framework/TextureQuad.h"
#include <set>

/**
 * Magic Block is used to provide animations for the newly created blocks on the screen 
 * It is ephemeral (i.e Time Limited) and when it is complete it should be removed 
 * The x and y Position are the lower left of Magic Block to be rendered.
 * 
 * Thus, if the Magic Block is to cover the area for a newly created Block (not a single game piece, 
 * but the scoring aggregate) then the x and y parameters should be from piece 0 (the lower left block)
 * The dimension is then 2 * the dimension of a single game piece.
 * 
 * Percent Complete will be used to render the alpha channel of the rendering where 
 * 100% complete (1.0f) is equivalent to total transparency
 */

class MagicBlock : public Rendered, public Themed, public TimeLimited
{
public:
	enum  BlockState { NONE=0, SHRINKER, SPARK, STAR, LOOPER };
private:	
	float _x;
	float _y;
	float _dim;
	//use board pos to indicated the underlying position in the board's array
	int _boardpos;

	BlockState _state;

	TextureQuad _quad;
	
	GLuint getNamedTexture(const char * arg); 
	
	GLuint getTexture();
	GLuint getMask();
	GLuint getSparkTexture();
	GLuint getSparkMask();
	GLuint getStarTexture();
	GLuint getStarMask();

	void drawShrinker();
	void drawSpark();
	void drawStar();
	void drawLooper();

	
public:

	MagicBlock(float x, float y, float dim, int boardpos);
	MagicBlock();
	virtual ~MagicBlock();

	virtual void setTheme(Theme *theme);
	void setState(BlockState state) { _state = state; };
	BlockState getState() { return _state; };
	void Draw();

	float getX() { return _x; };
	float getY() { return _y; };
	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };
	void setDim(float dim) { _dim = dim; };
	
	float getDim() { return _dim;}
	int getBoardPos() const { return _boardpos; } ;

	bool operator == (const MagicBlock &rhs) const { return getBoardPos() == rhs.getBoardPos();}; 


};

struct mbcomp{
	bool operator()(const MagicBlock &lhs, const MagicBlock &rhs) const{
		return lhs.getBoardPos() < rhs.getBoardPos();
	};
};

typedef std::set<MagicBlock ,mbcomp> MagicBlockSet;


#endif /*MAGICBLOCK_H_*/
