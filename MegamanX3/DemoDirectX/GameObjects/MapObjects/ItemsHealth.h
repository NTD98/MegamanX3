#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "GameObject.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
class ItemsHealth : public Entity
{
public:
	~ItemsHealth();
	ItemsHealth(float posX, float posY);
	void Update(float dt);
	void Draw(D3DXVECTOR2 transform);
	void OnCollision(Entity * impactor, SideCollisions side);
	bool isAlive = true;
protected:
	Animation *mAnimationHealth;
	

};