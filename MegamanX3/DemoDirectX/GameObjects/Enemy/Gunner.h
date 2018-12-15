#pragma once
#include"Enemy.h"
class Gunner : public Enemy
{
public:
	Gunner(D3DXVECTOR3 pos);
	~Gunner();
	void Shooting(D3DXVECTOR3 pos,bool isreverse);
	void Standing();
	void Jumpping(D3DXVECTOR3 pos);
	void Falling();
};
