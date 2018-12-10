#include "PlayerSpawingState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"

PlayerSpawingState::PlayerSpawingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerSpawingState::~PlayerSpawingState()
{
}

PlayerState::StateName PlayerSpawingState::GetState()
{
	return PlayerState::Spawning;
}

