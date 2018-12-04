#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
#include "../../GameComponents/Animation.h"
class Bullet :public Entity
{
public:
	Bullet(D3DXVECTOR3 pos,bool reverse);
	~Bullet();
	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void OnCollision();

	RECT GetBound();
protected:
	Sprite* bullet;
	Animation* destroyedbullet,
		mCurrentAnimaion,
		mChargeBullet1;
	bool isreverse;
	bool isdelete = false;
	float isDone=0.0f;
};
