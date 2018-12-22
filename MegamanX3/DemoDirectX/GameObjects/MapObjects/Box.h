#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "GameObject.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
class Box : public Entity
{
public:
	~Box();
	Box(float posX,float posY,int i);
	void Update(float dt);
	void ChooseBox(int i);
	void setHealth(Entity::EntityTypes entity);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void OnCollision(Entity *impactor, SideCollisions side);
	void Draw(D3DXVECTOR2 transform);
protected:
	Animation *mCurrentAnimation, *mBox2;
	bool isAlive = true;
	int health = 8;
};