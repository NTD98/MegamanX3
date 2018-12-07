#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(PlayerData *playerData);
	~PlayerRunningState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
	virtual StateName GetStateHaveShoot();

protected:
	float acceleratorX;
};

#pragma once