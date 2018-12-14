#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerDashState.h"
#include "PlayerDeadState.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData, bool isMoveToLeft,bool isMoveToRight)
{
	//Mặc định 2 biến isMoveToLeft , isMoveToRight = false
	// Nếu Player va chạm vào tường thì sẽ chuyển thành true
	//Nếu va chạm vào tường phía trái thì isMoveToLeft = true => AllowRunLeft = false => không cho phép chạy 
	//Nếu va chạm vào tường phía phải thì tương tự 
	if (isMoveToLeft == true) {
		AllowRunLeft = false;
	}
	else {
		AllowRunLeft = true;
	}

	if (isMoveToRight == true) {
		AllowRunRight = false;
	}
	else {
		AllowRunRight = true;
	}
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x44]) {
		this->mPlayerData->player->SetState(new PlayerDeadState(this->mPlayerData));
		return;
	}

	if (AllowRunLeft == false || AllowRunRight == false) {
		//Do nothing
	}
	else {
		if (keys[0x5A]) {
			this->mPlayerData->player->SetState(new PlayerDashState(this->mPlayerData));
			return;
		}
	}
	
	if (AllowRunLeft == true) {
		if (keys[VK_LEFT]) {
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
	}
	if (AllowRunRight == true) {
		if (keys[VK_RIGHT]) {
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
	}
	
	if (keys[0x58]) {
		this->mPlayerData->player->changeAnimation(PlayerState::StandShoot);
		return;
	}
	else {
		this->mPlayerData->player->changeAnimation(PlayerState::Standing);
		return;
	}
	return;
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}


