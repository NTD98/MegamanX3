#include "PlayerStandShootState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningShootState.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandShootState::PlayerStandShootState(PlayerData *playerData,bool isRunShootLeft,bool isRunShootRight)
{
	
	if (isRunShootLeft == true) {
		AllowRunShootLeft = false;
	}
	else {
		AllowRunShootLeft = true;
	}
	if (isRunShootRight == true) {
		AllowRunShootRight = false;
	}
	else {
		AllowRunShootRight = true;
	}
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerStandShootState::~PlayerStandShootState()
{
}

void PlayerStandShootState::HandleKeyboard(std::map<int, bool> keys)
{
	if (AllowRunShootLeft == true) {
		if (keys[VK_LEFT]) {
			this->mPlayerData->player->SetState(new PLayerRunningShootState(this->mPlayerData));
			return;
		}
	}
	if (AllowRunShootRight == true) {
		if (keys[VK_RIGHT]) {
			this->mPlayerData->player->SetState(new PLayerRunningShootState(this->mPlayerData));
			return;
		}
	}
	if (keys[0x58]) {
		return;
	}
	else {
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
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
