﻿#include "PlayerDashState.h"
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
	dtSmoke = 0.0f;
	dtSmokeAnimation = 0.1f;
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::HandleKeyboard(std::map<int, bool> keys)
{

	if (keys[0x58]) {
		if (this->mPlayerData->player->isChangeBullet == true) {
			this->mPlayerData->player->changeAnimation(PlayerState::Dash);
		}
		else {
			this->mPlayerData->player->changeAnimation(PlayerState::DashShoot);
		}
	}
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
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 8, 0);
				//Nếu đụng vào tường thì không cho phép chạy và phải đứng yên 
				//2 biến true và false ở dưới để thông báo cho state PlayerStandingState rằng vật đang va chạm vào hướng nào của player . (true = va chạm)
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData, true, false));
			}

			return;
		}

		case Entity::Right:
		{
			//va cham phia ben phai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->allowMoveRight = false;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 8), 0);
				//Nếu đụng vào tường thì không cho phép chạy và phải đứng yên 
				//2 biến true và false ở dưới để thông báo cho state PlayerStandingState rằng vật đang va chạm vào hướng nào của player . (true = va chạm)
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData, false, true));
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

