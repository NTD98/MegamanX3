#include "HeadGunnerFalling.h"
#include "HeadGunnerStandingState.h"
#include "Enemy.h"
HeadGunnerFalling::HeadGunnerFalling(EnemyData * EnemyData)
{
	this->mEnemyData = EnemyData;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
}

HeadGunnerFalling::~HeadGunnerFalling()
{
}

void HeadGunnerFalling::Update(float dt)
{
	this->mEnemyData->Enemy->AddVy(acceleratorY);
	if (mEnemyData->Enemy->GetVy() > 180)
	{
		mEnemyData->Enemy->SetVy(180);
	}
}

void HeadGunnerFalling::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
	this->mEnemyData->Enemy->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
	this->mEnemyData->Enemy->SetState(new HeadGunnerStandingState(this->mEnemyData));
	break;
	default:
		break;
	}
}

EnemyState::StateName HeadGunnerFalling::GetState()
{
	return EnemyState::Falling;
}
