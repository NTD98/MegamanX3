﻿#include "ChildHornet.h"
#include "../../GameDefines/GameDefine.h"
#include"../../GameComponents/CollisionManager.h"
ChildHornet::~ChildHornet()
{
}

ChildHornet::ChildHornet(int type, float posX, float posY, float vx, float vy)
{
	mAnimation = new Animation("Resources/Enemies/ChildHornet.png", "Resources/Enemies/ChildHornet.txt", 0.05f, true);
	this->vx = vx;
	this->vy = vy;
	if (vx < 0) {
		isFaceRight = true;
	}
	else isFaceRight = false;
	isAlive = true;
	isSpawn = true;
	waittingDie = false;
	tDelay = 0;
	dame = 1;
	typeAttack = type;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = EntityTypes::HornetChild;
}

ChildHornet::ChildHornet()
{
	isAlive = false;
}

void ChildHornet::Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject)
{
	if (isAlive) {
		if (typeAttack == 1) {	//Lao thẳng 1 hướng
			if (waittingDie) {
				tDelay += dt;
				if (tDelay > ChildHornetDefine::TIME_DELAY) {
					Die();
				}
			}
		}
		else if (typeAttack == 2) {	//Bay thẳng tới nhân vật

		}
		mAnimation->Update(dt,1);
		Entity::Update(dt);

		//kiểm tra va chạm  object với map
		for (size_t j = 0; j < mListMapObject.size(); j++) {
			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
		}

		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
			CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt);
		}
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);


	}
	if (mExplosion) {
		mExplosion->Update(dt);
	}
}

void ChildHornet::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall|| other->Tag == EntityTypes::Static) {
		if (typeAttack == 1) {
			waittingDie = true;
			vx = 0;
			vy = 0;
		}
		else if (typeAttack == 2) {
			int vxRand, vyRand;
			vxRand = rand() % 30 + 10;
			vyRand = rand() % 30 + 10;

			if (side == SideCollisions::Right || side == SideCollisions::BottomRight || side == SideCollisions::TopRight) {
				vxRand *= -1;
				if (vy < 0) vxRand *= -1;
			}
			if (side == SideCollisions::Bottom || side == SideCollisions::BottomLeft || side == SideCollisions::BottomRight) {
				if (vx<0) vxRand *= -1;
				vyRand *= -1;
			}
			vx = vxRand;
			vy = vyRand;
			if (vx > 0) {
				isFaceRight = false;
			}
			else {
				isFaceRight = true;
			}

		}
	}
	if (other->Tag == EntityTypes::Megaman) {
		Die();
	}
	else if (other->Tag == EntityTypes::BulletP || other->Tag == EntityTypes::BulletCharge1 || other->Tag == EntityTypes::BulletCharge2) {
		Die();
		other->Tag = EntityTypes::None;
	}
}

void ChildHornet::Die()
{
	waittingDie = false;
	isAlive = false;
	mExplosion = new Animation("Resources/explode.png", 6, 1, 6, 0.1f);
}

void ChildHornet::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		mAnimation->SetPosition(posX, posY);
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->Draw(transform);
	}
	
	if (mExplosion) mExplosion->Draw(transform);
}
