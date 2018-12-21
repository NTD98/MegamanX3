#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(PlayerData *playerData, bool isMoveToLeft = false,bool isMoveToRight=false);
    ~PlayerStandingState();

    void HandleKeyboard(std::map<int, bool> keys);
	void Update(float dt);
    virtual StateName GetState();
protected:
	bool AllowRunLeft = true, AllowRunRight = true;
};

