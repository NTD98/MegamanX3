#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingingState : public PlayerState
{
public:
	PlayerClingingState(PlayerData *playerData);
	~PlayerClingingState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
	virtual StateName GetStateHaveShoot();

protected:
	float acceleratorY;
	bool noPressedLeft,noPressedRight,noPressedSpace;
};


