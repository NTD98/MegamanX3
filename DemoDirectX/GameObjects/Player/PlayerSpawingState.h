#pragma once
#include "PlayerState.h"

class PlayerSpawingState : public PlayerState
{
public:
	PlayerSpawingState(PlayerData *playerData);
	~PlayerSpawingState();
	


	virtual StateName GetState();
	virtual StateName GetStateHaveShoot();
protected:
	
};

#pragma once
