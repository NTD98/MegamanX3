#pragma once
#include "PlayerState.h"

class PlayerStandShootState : public PlayerState
{
public:
	PlayerStandShootState(PlayerData *playerData,bool isRunShootLeft=false,bool isRunShootRight=false);
	~PlayerStandShootState();
	void HandleKeyboard(std::map<int, bool> keys);


	virtual StateName GetState();
	virtual StateName GetStateHaveShoot();
protected:
	bool AllowRunShootLeft = true, AllowRunShootRight = true;
};

#pragma once
