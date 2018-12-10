﻿#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerRunningShootState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    
    acceleratorX = 30.0f;

    this->mPlayerData->player->allowMoveLeft = true;
    this->mPlayerData->player->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x58]) {
		if (this->mPlayerData->player->allowMoveLeft == true && this->mPlayerData->player->allowMoveRight == true) {
			this->mPlayerData->player->SetState(new PLayerRunningShootState(this->mPlayerData));
			return;
		}
		return;
	}
    if (keys[VK_RIGHT])
    {
        if (mPlayerData->player->allowMoveRight)
        {
            mPlayerData->player->SetReverse(false);

            //di chuyen sang phai
            if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else if (keys[VK_LEFT])
    {
        if (mPlayerData->player->allowMoveLeft)
        {
            mPlayerData->player->SetReverse(true);

            //di chuyen sang trai
            if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

    switch (side)
    {
        case Entity::Left:
        {
            //va cham phia ben trai player
            if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->mPlayerData->player->allowMoveLeft = false;

                //day Player ra phia ben phai de cho player khong bi xuyen qua object
                this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left+0.2, 0);
				//Nếu đụng vào tường thì không cho phép chạy và phải đứng yên 
				//2 biến true và false ở dưới để thông báo cho state PlayerStandingState rằng vật đang va chạm vào hướng nào của player . (true = va chạm)
                this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData,true,false));
            }

            return;
        }

        case Entity::Right: 
        {
            //va cham phia ben phai player
            if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->mPlayerData->player->allowMoveRight = false;
                this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left+0.2), 0);
				//Nếu đụng vào tường thì không cho phép chạy và phải đứng yên 
				//2 biến true và false ở dưới để thông báo cho state PlayerStandingState rằng vật đang va chạm vào hướng nào của player . (true = va chạm)
                this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData,false,true));
            }
            return;
        }

        case Entity::Top:
            break;

        case Entity::Bottom: case Entity::BottomLeft : case Entity::BottomRight:           
        {
            this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

            this->mPlayerData->player->SetVy(0);

            return;
        }
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}

PlayerState::StateName PlayerRunningState::GetStateHaveShoot()
{
	return PlayerState::Running;
}
