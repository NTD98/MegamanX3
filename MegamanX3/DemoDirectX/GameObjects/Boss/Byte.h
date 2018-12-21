#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "bomp.h"
class Byte : public Entity
{
public:
	~Byte();
	Byte(float posX, float posY,Player* mPlayer,Camera* mCamera);
	void Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Shoot();
	void Slide();
	void Stand();
	void Draw(D3DXVECTOR2 transform);
	bool isshoot, isslide;
	bool right;
	float delay = 0.0f;
	Bomp* bomp;
protected:
	Player * mPlayer;
	Animation * mAnimation, *mAnimationSlidding, *mAnimationShooting, *mAnimationDying,*mAnimationStanding;
	
	vector<Bullet*> mListBullet;
	int typeAttack;
	float posX1, posY1;
	bool onDraw;
};
