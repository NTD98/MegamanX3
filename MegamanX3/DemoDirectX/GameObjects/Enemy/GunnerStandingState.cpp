#include "GunnerStandingState.h"
#include "Enemy.h"
#include "../../GameDefines/GameDefine.h"

GunnerStandingState::GunnerStandingState(EnemyData *EnemyData)
{
	this->mEnemyData = EnemyData;
	this->mEnemyData->Enemy->SetVx(0);
	this->mEnemyData->Enemy->SetVy(0);
}


GunnerStandingState::~GunnerStandingState()
{
}

EnemyState::StateName GunnerStandingState::GetState()
{
	return EnemyState::Standing;
}
