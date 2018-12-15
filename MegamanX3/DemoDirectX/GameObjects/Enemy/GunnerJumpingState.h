#pragma once
#include "EnemyState.h"
#include "Enemy.h"
class GunnerJumpingState : public EnemyState
{
public:
	GunnerJumpingState(EnemyData *EnemyData,D3DXVECTOR3 pos);
	~GunnerJumpingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
	D3DXVECTOR3 pos;
};

