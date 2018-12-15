#pragma once
#include "EnemyState.h"

class GunnerShootingState : public EnemyState
{
public:
	GunnerShootingState(EnemyData *EnemyData,D3DXVECTOR3 pos);
	void Update(float dt);
	~GunnerShootingState();

	virtual StateName GetState();

protected:
	D3DXVECTOR3 position;
};
