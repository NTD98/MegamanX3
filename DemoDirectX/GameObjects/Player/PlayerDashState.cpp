#include "PlayerDashState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
PlayerDashState::PlayerDashState(PlayerData * playerData)
{
	this->mPlayerData = playerData;

	acceleratorX = 20.0f;

	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x58]) {
		//this->mPlayerData->player->SetState(new PlayerDashShootState(this->mPlayerData));
		
		return;
	}
	//if (keys[VK_RIGHT])
	//{
	//	if (mPlayerData->player->allowMoveRight)
	//	{
	//		mPlayerData->player->SetReverse(false);

	//		//di chuyen sang phai
	//		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_DASHING_SPEED)
	//		{
	//			this->mPlayerData->player->AddVx(acceleratorX);

	//			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_DASHING_SPEED)
	//			{
	//				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_DASHING_SPEED);
	//			}
	//		}
	//	}
	//}
	//else if (keys[VK_LEFT])
	//{
	//	if (mPlayerData->player->allowMoveLeft)
	//	{
	//		mPlayerData->player->SetReverse(true);

	//		//di chuyen sang trai
	//		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_DASHING_SPEED)
	//		{
	//			this->mPlayerData->player->AddVx(-acceleratorX);

	//			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_DASHING_SPEED)
	//			{
	//				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_DASHING_SPEED);
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	//	return;
	//}
}

void PlayerDashState::Update(float dt)
{
	
	if (this->mPlayerData->player->GetReverse())
		{
			this->mPlayerData->player->SetReverse(true);
			if (mPlayerData->player->allowMoveRight)
			{
				//di chuyen sang phai
				if (this->mPlayerData->player->GetVx() >= -Define::PLAYER_MAX_DASHING_SPEED)
				{
					this->mPlayerData->player->AddVx(-acceleratorX);

					if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_DASHING_SPEED)
					{
						this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
					}
				}
			}
		}
		else
			if (!this->mPlayerData->player->GetReverse())
			{
				this->mPlayerData->player->SetReverse(false);
				if (mPlayerData->player->allowMoveLeft)
				{
					//di chuyen sang phai
					if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_DASHING_SPEED)
					{
						this->mPlayerData->player->AddVx(acceleratorX);

						if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_DASHING_SPEED)
						{
							this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
						}
					}
				}
	}
	
	
}

void PlayerDashState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
		case Entity::Left:
		{
			//va cham phia ben trai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->allowMoveLeft = false;

				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 10, 0);

				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}

			return;
		}

		case Entity::Right:
		{
			//va cham phia ben phai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->allowMoveRight = false;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 10), 0);
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
			return;
		}

		case Entity::Top:
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			this->mPlayerData->player->SetVy(0);

			return;
		}
	}
}

PlayerState::StateName PlayerDashState::GetState()
{
	return PlayerState::Dash;
}

PlayerState::StateName PlayerDashState::GetStateHaveShoot()
{
	return PlayerState::DashShoot;
}
