#pragma once
#include "EnemyState.h"

class HeadGunnerStandingState : public EnemyState
{
public:
	HeadGunnerStandingState(EnemyData *EnemyData);
	~HeadGunnerStandingState();

	virtual StateName GetState();

protected:
};
