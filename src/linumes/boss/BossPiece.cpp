#include "BossPiece.h"
#include "BossModeTypes.h"

BossPiece::BossPiece() : GamePiece(), _boss(false), _bossTexture(0) {
    
}

BossPiece::~BossPiece() {

}

bool BossPiece::isStopped() {
    if (_boss) {
        return true;
    }
    return GamePiece::isStopped();
}

void BossPiece::bindStateTexture() {
    if (_boss && !isScanned() && !isSpecial() ) {
       	glBindTexture( GL_TEXTURE_2D, _bossTexture );
    	glColor3f(1.0f,1.0f,1.0f);
    } else {
        GamePiece::bindStateTexture();
    }
}
