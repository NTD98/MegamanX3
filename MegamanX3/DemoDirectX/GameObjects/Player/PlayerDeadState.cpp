#include "PlayerDeadState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerDeadState::PlayerDeadState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	
}


PlayerDeadState::~PlayerDeadState()
{
	
}

void PlayerDeadState::HandleKeyboard(std::map<int, bool> keys)
{
	
}

PlayerState::StateName PlayerDeadState::GetState()
{
	return PlayerState::Dead;
}


