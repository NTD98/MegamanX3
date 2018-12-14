#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(PlayerData *playerData, bool isMoveToLeft = false,bool isMoveToRight=false);
    ~PlayerStandingState();

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();
protected:
	bool AllowRunLeft = true, AllowRunRight = true;
};

