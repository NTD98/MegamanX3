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
	void Draw(D3DXVECTOR2 transform);
	void SetState(EnemyState *newState);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	MoveDirection getMoveDirection();
	void OnNoCollisionWithBottom();
	RECT GetBound();

	EnemyState::StateName Enemy::getState();

	void changeAnimation(EnemyState::StateName state);
	Animation* getCurrentAnimation();
	//true thi se lat nguoc anh theo truc y
	void setjumptime();
	float getjumptime();
	void setshoottime();
	float getshoottime();
	float getisdone();
	void setisdone();
	void SetReverse(bool flag);
	bool GetReverse();
	void setJump(bool allowjump);
	bool isDone = false;
	bool allowMoveLeft;
	bool allowMoveRight;
	int getHealthPoint();
	void setHealthPoint(Entity::EntityTypes entityType);
	float isdoneAnimation = 0.0f;
	EnemyData* getEnemydata();
	bool allowjump = true;
	bool isAlive;
	virtual void Shooting(D3DXVECTOR3 pos, bool isreverse);
	virtual void Standing();
	virtual void Jumpping(D3DXVECTOR3 pos);
	virtual void Falling();
protected:
	float Jumptime=0.0f,Shoottime=0.0f;
	Camera * mCamera;

	EnemyData *mEnemyData;

	Animation   *mCurrentAnimation,
		*mAnimationShooting,
		*mAnimationStanding,
		*mAnimationJumping;
	int HealthPoint = 16;
	EnemyState::StateName mCurrentState;

	//chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool mCurrentReverse, allowshoot = true;
};


