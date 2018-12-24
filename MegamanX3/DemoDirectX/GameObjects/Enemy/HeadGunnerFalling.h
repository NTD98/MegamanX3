#pragma once
#include "EnemyState.h"
#include "Enemy.h"

class HeadGunnerFalling : public EnemyState
{
public:
	HeadGunnerFalling(EnemyData *EnemyData);
	~HeadGunnerFalling();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;

	//neu nhu van toc ban dau = khong thi se khong cho giam toc do
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;
};


