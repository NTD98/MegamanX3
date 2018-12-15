#pragma once
#include "EnemyState.h"

class GunnerStandingState : public EnemyState
{
public:
	GunnerStandingState(EnemyData *EnemyData);
	~GunnerStandingState();

	virtual StateName GetState();

protected:
};
