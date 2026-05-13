#ifndef BOSSICON_H_
#define BOSSICON_H_

#include "linumes/Icon.h"

namespace Linumes {

class BossIcon : public Icon
{
private:
	GLuint _bossTexture;
	GLuint _bossMask;
public:
	BossIcon();
	virtual ~BossIcon();
	void setBossTexture( GLuint t){ _bossTexture = t; };
	void setBossMask( GLuint t){ _bossMask= t; };
protected:
	virtual  GLuint getTexture(int which) {return ( which == 0 ? _bossMask : _bossTexture );};
};

} // namespace Linumes

#endif /*BOSSICON_H_*/
