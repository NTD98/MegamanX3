#include "HeadGunnerStandingState.h"
#include "Enemy.h"
#include "../../GameDefines/GameDefine.h"

HeadGunnerStandingState::HeadGunnerStandingState(EnemyData *EnemyData)
{
	this->mEnemyData = EnemyData;
	this->mEnemyData->Enemy->SetVx(0);
	this->mEnemyData->Enemy->SetVy(0);
}


HeadGunnerStandingState::~HeadGunnerStandingState()
{
}

EnemyState::StateName HeadGunnerStandingState::GetState()
{
	return EnemyState::Standing;
}
