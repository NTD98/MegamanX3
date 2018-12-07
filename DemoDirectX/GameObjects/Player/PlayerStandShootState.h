#pragma once
#include "PlayerState.h"

class PlayerStandShootState : public PlayerState
{
public:
	PlayerStandShootState(PlayerData *playerData);
	~PlayerStandShootState();
	void HandleKeyboard(std::map<int, bool> keys);


	virtual StateName GetState();

protected:
};

#pragma once
