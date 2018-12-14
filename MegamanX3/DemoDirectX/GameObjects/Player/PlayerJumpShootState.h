#pragma once
#include "PlayerJumpingState.h"
class PlayerJumpShootState : public PlayerJumpingState {
	PlayerJumpShootState();
	~PlayerJumpShootState();
	virtual StateName GetState();
};