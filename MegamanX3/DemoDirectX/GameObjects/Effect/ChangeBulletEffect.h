#pragma once

#include "../Entity.h"
#include "../../GameComponents/Animation.h"
#include "../Player/Player.h"

class ChangeBulletEffect : public Entity {
public:

	ChangeBulletEffect();
	~ChangeBulletEffect();
	void Update(float dt,Player *mplayer);
	void Draw(D3DXVECTOR2 Trans = D3DXVECTOR2());
protected:
	Animation *mCurrentAnimation, *mEffectChangeBullet1, *mEffectChangeBullet2;
	D3DXVECTOR2 trans;

};



