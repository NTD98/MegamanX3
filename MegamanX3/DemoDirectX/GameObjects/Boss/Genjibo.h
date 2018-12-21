#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "../../GameDefines/GameDefine.h"
class Genjibo : public Entity
{
public:
	~Genjibo();
	Genjibo(float posX, float posY);
	void Update(float dt,Player* mPlayer, vector<Entity*> mListMapObject);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	float type2 = 0.0f;
	bool check2 = false;
	void Draw(D3DXVECTOR2 transform);
protected:
	Animation *mAnimation, *mAnimationSpawn, *mAnimationSub, *mAnimationRotate;
	Sprite *mSpriteZone;
	vector<Bullet*> mListBullet;
	int typeAttack;
	float posX1, posY1;
	bool onDraw;
};
