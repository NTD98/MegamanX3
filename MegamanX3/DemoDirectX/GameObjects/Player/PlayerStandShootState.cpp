#include "PlayerStandShootState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningShootState.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandShootState::PlayerStandShootState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerStandShootState::~PlayerStandShootState()
{
}

void PlayerStandShootState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT]) {
		this->mPlayerData->player->SetState(new PLayerRunningShootState(this->mPlayerData));
		return;
	}
	else {
		if (keys[0x58]) {
			return;
		}
		else {
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		}
		
	}
	
}

PlayerState::StateName PlayerStandShootState::GetState()
{
	return PlayerState::StandShoot;
}

PlayerState::StateName PlayerStandShootState::GetStateHaveShoot()
{
	return PlayerState::StandShoot;
}
