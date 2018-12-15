#pragma once

#include "../Entity.h"
#include "../../GameComponents/Animation.h"

class PlayerFlashDashEffect : public Entity {
public:

	PlayerFlashDashEffect();
	~PlayerFlashDashEffect();
	void SetPos(float posX,float posY);
	void Update(float dt, D3DXVECTOR3 pos, bool isreverse,int PlayerSizeWidth,int PlayerSizeHeight);
	void Draw(bool isreverse = false,D3DXVECTOR2 Trans= D3DXVECTOR2());
protected:
	Animation *mPlayerFlashDash;
	bool isreverse = false;
	D3DXVECTOR2 trans;

};



