#pragma once
#include "EnemyData.h"
#include "../Entity.h"
#include "../../GameComponents/GameCollision.h"
#include <map>

class EnemyState
{
public:
	enum StateName
	{
		Standing,
		Die,
		Shooting,
		Jump
	};

	~EnemyState();

	virtual void Update(float dt);

	virtual void HandleKeyboard(std::map<int, bool> keys);

	//side va cham voi Enemy
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState() = 0;

protected:
	EnemyState(EnemyData *EnemyData);
	EnemyState();

	EnemyData *mEnemyData;
};


