#pragma once
#include "PlayerState.h"


class PlayerDameState : public PlayerState
{
public:
	PlayerDameState(PlayerData *playerData);
	~PlayerDameState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void Update(float dt);

	virtual StateName GetState();
protected:
	float dtTimeBeDame;
	bool isOnCollision;
};

#pragma once
