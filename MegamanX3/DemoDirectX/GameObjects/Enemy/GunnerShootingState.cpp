#include "GunnerShootingState.h"
#include "Enemy.h"
GunnerShootingState::GunnerShootingState(EnemyData * EnemyData,D3DXVECTOR3 pos)
{
	this->mEnemyData = EnemyData;
	position = pos;
}

void GunnerShootingState::Update(float dt)
{
	if (position.x > this->mEnemyData->Enemy->GetPosition().x)
		this->mEnemyData->Enemy->SetReverse(true);
	else
		this->mEnemyData->Enemy->SetReverse(false);
}

GunnerShootingState::~GunnerShootingState()
{
	delete this;
}

EnemyState::StateName GunnerShootingState::GetState()
{
	return StateName::Shooting;
}
