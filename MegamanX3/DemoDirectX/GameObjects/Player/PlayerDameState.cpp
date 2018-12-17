#include "PlayerDameState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerDameState::PlayerDameState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerDameState::~PlayerDameState()
{
}

void PlayerDameState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (this->isOnCollision==true) {
		this->mPlayerData->player->isSetHealth = true;
	}
}

void PlayerDameState::Update(float dt)
{
	if (this->mPlayerData->player->isTimeNoDame == false) // Khong o trong trang thai bat kha xam pham
	{
		this->mPlayerData->player->isTimeNoDame = true;
		this->isOnCollision = true;
	}
	else {
		this->isOnCollision = false;
	}
}


PlayerState::StateName PlayerDameState::GetState()
{
	return PlayerState::BeDame;
}

