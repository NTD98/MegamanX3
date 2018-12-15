#include "GunnerJumpingState.h"
#include "GunnerStandingState.h"
#include "GunnerFallingState.h"
GunnerJumpingState::GunnerJumpingState(EnemyData * EnemyData,D3DXVECTOR3 pos)
{
	this->mEnemyData = EnemyData;
	this->mEnemyData->Enemy->SetVy(-280);
	this->pos = pos;
	acceleratorY = 10.0f;
	acceleratorX = 100.0f;
}

GunnerJumpingState::~GunnerJumpingState()
{
}

void GunnerJumpingState::Update(float dt)
{
	
	if (this->mEnemyData->Enemy->GetPosition().x > pos.x)
	{
		if (this->mEnemyData->Enemy->GetVy() >= 0)
		{
			this->mEnemyData->Enemy->SetState(new GunnerFallingState(this->mEnemyData));
			return;
		}
		if (this->mEnemyData->Enemy->GetVy() < 0)
			this->mEnemyData->Enemy->AddVy(acceleratorY);
		if (this->mEnemyData->Enemy->GetPosition().x >= (this->mEnemyData->Enemy->GetPosition().x + pos.x) / 2)
		{
			mEnemyData->Enemy->SetReverse(false);
			//Enemy dang di chuyen sang ben trai      
			if (mEnemyData->Enemy->GetVx() >= 0)
			{
				this->mEnemyData->Enemy->AddVx(-acceleratorX);

				if (mEnemyData->Enemy->GetVx() > 0)
					this->mEnemyData->Enemy->SetVx(0);
			}
		}
	}
	else if (this->mEnemyData->Enemy->GetPosition().x <= pos.x)
	{
		if (this->mEnemyData->Enemy->GetVy() >= 0)
		{
			this->mEnemyData->Enemy->SetState(new GunnerFallingState(this->mEnemyData));
			return;
		}
		if (this->mEnemyData->Enemy->GetVy() < 0)
			this->mEnemyData->Enemy->AddVy(acceleratorY);
		if (this->mEnemyData->Enemy->GetPosition().x <= (this->mEnemyData->Enemy->GetPosition().x + pos.x) / 2)
		{
			mEnemyData->Enemy->SetReverse(true);
			//Enemy dang di chuyen sang phai   
			if (mEnemyData->Enemy->GetVx() <= 0)
			{
				this->mEnemyData->Enemy->AddVx(acceleratorX);

				if (mEnemyData->Enemy->GetVx() < 0)
					this->mEnemyData->Enemy->SetVx(0);
			}
		}
	}
	else
	{
		this->mEnemyData->Enemy->SetState(new GunnerFallingState(this->mEnemyData));
	}

}

void GunnerJumpingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
		case Entity::Left:
		{
			this->mEnemyData->Enemy->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mEnemyData->Enemy->SetVx(0);
			break;
		}

		case Entity::Right:
		{
			this->mEnemyData->Enemy->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mEnemyData->Enemy->SetVx(0);
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			this->mEnemyData->Enemy->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			this->mEnemyData->Enemy->SetVy(0);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->mEnemyData->Enemy->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		}

		default:
			break;
	}
}

EnemyState::StateName GunnerJumpingState::GetState()
{
	return EnemyState::Jumping;
}
