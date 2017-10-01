#ifndef BOSSPIECE_H
#define BOSSPIECE_H

#include "linumes/GamePiece.h"

class BossPiece : public GamePiece {
private:
    bool _boss;
    GLuint _bossTexture;
protected:
  virtual void bindStateTexture();
public:
    BossPiece();
    virtual ~BossPiece();
    bool isBoss() { return _boss; };
    void setBoss(bool boss) { _boss = boss; };
    void setBossTexture(GLuint texture) { _bossTexture = texture; };
    virtual bool isStopped();
};

#endif
