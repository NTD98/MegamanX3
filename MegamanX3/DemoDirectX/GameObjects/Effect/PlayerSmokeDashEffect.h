#pragma once

#include "../Entity.h"
#include "../../GameComponents/Animation.h"

class PlayerSmokeDashEffect : public Entity {
public:

	PlayerSmokeDashEffect();
	~PlayerSmokeDashEffect();
	void Update(float dt, D3DXVECTOR3 pos, bool isreverse, int PlayerSizeWidth, int PlayerSizeHeight);
	void Draw(bool isreverse = false, D3DXVECTOR2 Trans = D3DXVECTOR2());
protected:
	Animation *mPlayerSmokeDash;
	bool isreverse = false;
	D3DXVECTOR2 trans;

};



