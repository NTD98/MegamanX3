#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDashState : public PlayerState
{
public:
	PlayerDashState(PlayerData *playerData);
	~PlayerDashState();

	void HandleKeyboard(std::map<int, bool> keys);
	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
	

protected:
	float acceleratorX;
};

