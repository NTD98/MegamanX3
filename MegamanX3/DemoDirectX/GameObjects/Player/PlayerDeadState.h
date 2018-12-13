#pragma once
#include "PlayerState.h"

class PlayerDeadState : public PlayerState
{
public:
	PlayerDeadState(PlayerData *playerData);
	~PlayerDeadState();

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
};

