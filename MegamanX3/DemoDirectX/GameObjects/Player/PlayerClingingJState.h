#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingingJState : public PlayerState
{
public:
	PlayerClingingJState(PlayerData *playerData);
	~PlayerClingingJState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
	virtual StateName GetStateHaveShoot();

protected:
	float acceleratorX, acceleratorY;
	bool noPressed;
	Entity::SideCollisions sidetemp;
};



