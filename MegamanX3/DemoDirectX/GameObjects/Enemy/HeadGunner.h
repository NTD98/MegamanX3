#pragma once
#include"Enemy.h"
class HeadGunner : public Enemy
{
public:
	HeadGunner(D3DXVECTOR3 pos);
	~HeadGunner();
	void Shooting(D3DXVECTOR3 pos, bool isreverse);
	void Standing();
};

