﻿#include "EnemyBullet.h"
#include "../../GameDefines/GameDefine.h"

EnemyBullet::EnemyBullet()
{
	mSprite1 = new Sprite("Resources/enemy/EnemyBullet.png");
 
	this->Tag = EntityTypes::EnemyBullets1;
	wasBorn = false;
	typeBullet = 1;
}
EnemyBullet::EnemyBullet(int headgunner)
{
	this->Tag = EntityTypes::EnemyBullets2;
	mHeadGunnerBullet = new Animation("Resources/Headgunnerbullet.png", 2, 1, 2, 0.2f);
	wasBorn = false;
	typeBullet = 2;
}
EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Spawn(int type,float posx, float posy, float vx, float vy)
{
	this->SetPosition(posx,posy);
	this->vx = vx;
	this->vy = vy;
	typeBullet = type;
	if (type == 1) {
		ay = GunnerDefine::BULLET_ACCELERATOR_Y;
		this->SetWidth(mSprite1->GetWidth());
		this->SetHeight(mSprite1->GetHeight());
	}
	else if (type == 2)
	{
		ay = GunnerDefine::BULLET_ACCELERATOR_Y;
		this->SetWidth(mHeadGunnerBullet->GetWidth());
		this->SetHeight(mHeadGunnerBullet->GetHeight());
	}
	wasBorn = true;
}

void EnemyBullet::Update(float dt)
{
	if (wasBorn) {
		vy += ay;
		Entity::Update(dt);
	}
	if (mExplosion!=NULL) {
		mExplosion->Update(dt);
	}
}

void EnemyBullet::OnCollision(Entity * other, SideCollisions side)
{
	if (this->Tag != EntityTypes::None) {
		wasBorn = false;
		mExplosion = new Animation("Resources/explode.png", 6, 1, 6, 0.1);
		if (typeBullet == 1)
			mExplosion->SetPosition(mSprite1->GetPosition());
		else if (typeBullet == 2)
			mExplosion->SetPosition(mHeadGunnerBullet->GetPosition());
		this->Tag = EntityTypes::None;
	}
}

void EnemyBullet::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn) {
		if (typeBullet == 1) {
			mSprite1->SetPosition(posX, posY);
			mSprite1->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
		else if (typeBullet == 2)
		{
			mHeadGunnerBullet->SetPosition(posX, posY);
			mHeadGunnerBullet->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
	}
	if (mExplosion && !mExplosion->isEndAnimate) {
		mExplosion->Draw(transform);
	}
}
