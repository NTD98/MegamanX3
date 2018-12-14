#pragma once
#ifndef _PlayerEffect_h
#define _PlayerEffect_h
#include "../Entity.h"
#include "../../GameComponents/Animation.h"

class PlayerEffect : public Entity {
public:

	PlayerEffect();
	~PlayerEffect();
	void SetPos(float posX,float posY);
	void Update(float dt, D3DXVECTOR3 pos, bool isreverse,int PlayerSizeWidth,int PlayerSizeHeight);
	void Draw(bool isreverse = false,D3DXVECTOR2 Trans= D3DXVECTOR2());
protected:
	Animation *mPlayerEffectDash;
	bool isreverse = false;
	D3DXVECTOR2 trans;

};


#endif
