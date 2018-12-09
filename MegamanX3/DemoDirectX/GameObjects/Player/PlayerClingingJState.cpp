#include "PlayerClingingJState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerClingingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerClingingJState::PlayerClingingJState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(-400);
	this->mPlayerData->player->SetVx(0);
	acceleratorY = 10.0f;
	acceleratorX = 40.0f;
}

PlayerClingingJState::~PlayerClingingJState()
{
}

void PlayerClingingJState::Update(float dt)
{
	this->mPlayerData->player->AddVx(acceleratorX);
	this->mPlayerData->player->AddVy(acceleratorY);
	if (mPlayerData->player->GetVy() >=0)
	{
		mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		return;
	}

		if (sidetemp==Entity::Left)
		{
			//player dang di chuyen sang ben trai      
				this->mPlayerData->player->AddVx(acceleratorX);
				if (this->mPlayerData->player->GetVx() >= 100)
					this->mPlayerData->player->SetVx(0);
		}
		else if (sidetemp==Entity::Right)
		{
			//player dang di chuyen sang phai   
			if (this->mPlayerData->player->GetVx() < -100)
				this->mPlayerData->player->SetVx(0);
				this->mPlayerData->player->SetVx(-acceleratorX);

		}
}

void PlayerClingingJState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < 200)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() >= 20)
			{
				this->mPlayerData->player->SetVx(100);
			}
		}

		noPressed = false;
	}
	else if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -100)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() < -100)
			{
				this->mPlayerData->player->SetVx(-100);
			}
		}

		noPressed = false;
	}
	else
	{
		noPressed = true;
	}
}

void PlayerClingingJState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	sidetemp = side;
	switch (side)
	{
	case Entity::Left:
	{
		this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
		this->mPlayerData->player->SetVx(0);
		/*if (noPressed == false)
		{
			this->mPlayerData->player->SetVy(0);
			this->mPlayerData->player->SetState(new PlayerClingingState(this->mPlayerData));
		}*/
		break;
	}

	case Entity::Right:
	{
		this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
		this->mPlayerData->player->SetVx(0);
		/*if (noPressed == false)
		{

			this->mPlayerData->player->SetState(new PlayerClingingState(this->mPlayerData));
		}*/
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		this->mPlayerData->player->SetVy(0);
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
	}

	default:
		break;
	}
}

PlayerState::StateName PlayerClingingJState::GetState()
{
	return PlayerState::ClingingJ;
}

PlayerState::StateName PlayerClingingJState::GetStateHaveShoot()
{
	return PlayerState::ClingingJShoot;
}
