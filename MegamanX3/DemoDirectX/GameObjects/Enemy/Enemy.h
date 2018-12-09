#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "EnemyData.h"
#include "EnemyState.h"
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	enum MoveDirection
	{
		MoveToLeft, //chay tu phai sang trai
		MoveToRight, //chay tu trai sang phai
		None //dung im
	};

	void SetCamera(Camera *camera);

	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(EnemyState *newState);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	MoveDirection getMoveDirection();

	RECT GetBound();

	EnemyState::StateName Enemy::getState();

	void changeAnimation(EnemyState::StateName state);
	Animation* getCurrentAnimation();
	//true thi se lat nguoc anh theo truc y
	void SetReverse(bool flag);
	bool GetReverse();
	bool isDone = false;
	bool allowMoveLeft;
	bool allowMoveRight;
	int getHealthPoint();
	EnemyData* getEnemydata();
protected:

	Camera * mCamera;

	EnemyData *mEnemyData;

	Animation   *mCurrentAnimation,
		*mAnimationStanding,
		*mAnimationJumping;
	int HealthPoint = 16;
	EnemyState::StateName mCurrentState;

	//chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool mCurrentReverse, allowshoot = true;
};


