#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "GameObject.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
class Elevator : public Entity
{
public:
	~Elevator();
	Elevator(D3DXVECTOR3 pos);
	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	void Draw(D3DXVECTOR2 transform);
	void OnSetPosition(D3DXVECTOR3 poks);
protected:
	Animation *mAnimation;
};