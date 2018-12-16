#pragma once
#include "EnemyState.h"

class HeadGunnerShootingState : public EnemyState
{
public:
	HeadGunnerShootingState(EnemyData *EnemyData, D3DXVECTOR3 pos);
	void Update(float dt);
	~HeadGunnerShootingState();

	virtual StateName GetState();

protected:
	D3DXVECTOR3 position;
};
