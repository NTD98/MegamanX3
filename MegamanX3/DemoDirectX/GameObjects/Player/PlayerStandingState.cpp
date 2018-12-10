#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
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
		//Nếu Player đang va chạm  vào tường bên trái và bắn => truyền một biến cho state PlayerStandShootState thông báo 
		// rằng không cho phép chạy state PlayerRuningState về phía bên trái
		if (AllowRunLeft == false) {
			this->mPlayerData->player->SetState(new PlayerStandShootState(this->mPlayerData, true,false));
			return;
		}
		//Nếu Player đang va chạm  vào tường bên phải và bắn=> truyền một biến cho state PlayerStandShootState thông báo 
		// rằng không cho phép chạy state PlayerRuningState về phía bên phải
		if (AllowRunRight == false) {
			this->mPlayerData->player->SetState(new PlayerStandShootState(this->mPlayerData, false,true));
			return;
		}
		//Trường hợp không va chạm thì chạy và bắn tự do 
		this->mPlayerData->player->SetState(new PlayerStandShootState(this->mPlayerData, false, false));
		return;
	}
	return;
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}

PlayerState::StateName PlayerStandingState::GetStateHaveShoot()
{
	return PlayerState::Standing;
}

