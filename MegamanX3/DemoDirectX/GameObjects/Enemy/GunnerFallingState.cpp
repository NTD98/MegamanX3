#include "GunnerFallingState.h"
#include "GunnerStandingState.h"
#include "Enemy.h"
GunnerFallingState::GunnerFallingState(EnemyData * EnemyData)
{
	this->mEnemyData = EnemyData;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
}

GunnerFallingState::~GunnerFallingState()
{
}

void GunnerFallingState::Update(float dt)
{
	this->mEnemyData->Enemy->AddVy(acceleratorY);
	if (mEnemyData->Enemy->GetVy() > 180)
	{
		mEnemyData->Enemy->SetVy(180);
	}
}

void GunnerFallingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 6.0f)
		{
			this->mEnemyData->Enemy->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			this->mEnemyData->Enemy->SetState(new GunnerStandingState(this->mEnemyData));

		}
		return;

	default:
		break;
	}
}

EnemyState::StateName GunnerFallingState::GetState()
{
	return EnemyState::Falling;
}
