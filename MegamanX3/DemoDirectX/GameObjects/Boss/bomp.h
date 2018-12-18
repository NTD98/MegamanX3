#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
class Bomp :public Entity
{
public:
	Bomp(D3DXVECTOR3 pos, bool reverse);
	~Bomp();
	void Draw(D3DXVECTOR2 transform);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	bool isdestoyed;
protected:
	Animation * bomp,
		*flybomp,
		*destroyedbomp,
		*clingbomp;
	bool isreverse;

};