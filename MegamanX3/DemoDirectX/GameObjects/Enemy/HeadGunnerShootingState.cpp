#include "HeadGunnerShootingState.h"
#include "Enemy.h"
HeadGunnerShootingState::HeadGunnerShootingState(EnemyData * EnemyData, D3DXVECTOR3 pos)
{
	this->mEnemyData = EnemyData;
	position = pos;
}

void HeadGunnerShootingState::Update(float dt)
{
	if (position.x > this->mEnemyData->Enemy->GetPosition().x)
		this->mEnemyData->Enemy->SetReverse(true);
	else
		this->mEnemyData->Enemy->SetReverse(false);
}

HeadGunnerShootingState::~HeadGunnerShootingState()
{
	delete this;
}

EnemyState::StateName HeadGunnerShootingState::GetState()
{
	return StateName::Shooting;
}
