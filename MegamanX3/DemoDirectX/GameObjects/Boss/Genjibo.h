#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
class Genjibo : public Entity
{
public:
	~Genjibo();
	Genjibo(float posX, float posY);
	void Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	float type2 = 0.0f, type4 = 0.0f;
	bool check2 = false, check4 = 0.0f;
	void Draw(D3DXVECTOR2 transform);
	bool isChange;
	Animation* mExplode[5];
	int count = 0;
protected:
	Animation * mAnimation, *mAnimationSpawn, *mAnimationSub, *mAnimationRotate, *mAnimationCircle, *mAnimationDie;
	Sprite *mSpriteZone;
	vector<Bullet*> mListBullet;	
	int typeAttack;
	float posX1, posY1;
	bool onDraw;
};
