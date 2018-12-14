#include "PlayerClingingState.h"
#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerClingingJState.h"
#include "../../GameDefines/GameDefine.h"
Entity::SideCollisions tempside;
PlayerClingingState::PlayerClingingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;

	acceleratorY = 25.0f;
}

PlayerClingingState::~PlayerClingingState()
{
}

void PlayerClingingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);
	if ((noPressedLeft==true&&tempside==Entity::Left) )
	{
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
		noPressedSpace = false;
	}
}

void PlayerClingingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x58]) {
		this->mPlayerData->player->changeAnimation(PlayerState::ClingingShoot);
	}
	else {
		this->mPlayerData->player->changeAnimation(PlayerState::Clinging);
	}
	if (keys[VK_RIGHT])
	{
		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->SetVy(0);
			this->mPlayerData->player->AddVy(acceleratorY);
		}
		if (keys[VK_SPACE])
		{
			if (noPressedSpace == true)
				this->mPlayerData->player->SetState(new PlayerClingingJState(this->mPlayerData));
			noPressedSpace = false;
		}
		noPressedRight = false;
	}
 	else if (keys[VK_LEFT])
	{
		this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->AddVy(acceleratorY);
		//di chuyen sang trai

		noPressedLeft = false;
		if (keys[VK_SPACE])
		{
			if (noPressedSpace == true)
				this->mPlayerData->player->SetState(new PlayerClingingJState(this->mPlayerData));
			noPressedSpace = false;
		}
	}
	else
	{
		noPressedLeft = noPressedRight= true;
	}
	
}

void PlayerClingingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	tempside = side;
	switch (side)
	{
		case Entity::Left:
		{
			mPlayerData->player->SetReverse(true);
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
			break;
		}

		case Entity::Right:
		{
			mPlayerData->player->SetReverse(false);
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
			break;
		}
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
	}
}

PlayerState::StateName PlayerClingingState::GetState()
{
	return PlayerState::Clinging;
}
