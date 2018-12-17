﻿#include "Genjibo.h"
#include "../../GameComponents/CollisionManager.h"
Genjibo::~Genjibo()
{
}

Genjibo::Genjibo(float posX, float posY)
{
	mAnimationSpawn = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboSpawn.txt", 0.1f, false);
	mAnimationRotate= new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboRotateLeft.txt", 0.001f, true);
	mAnimationSub= new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/SubGenjibo.txt", 0.01f, false);
	mSpriteZone = new Sprite("Resources/Boss/GenjiboZone.png");

	mAnimation = mAnimationSpawn;
	isFaceRight = false;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	mSpriteZone->SetPosition(posX, posY-5);
	mAnimationSub->SetPosition(posX, posY - 200);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());

	posX1 = posX;
	posY1 = posY;
	hp = 20;
	vx = 100;
	vy = 20;
	dame = 2;
	isAlive = true;
	isSpawn = true;
	onDraw = false;
	typeAttack = 0;
	this->Tag = EntityTypes::Genjibo;
}

void Genjibo::Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject)
{
	if (isAlive ) {
	//boss go down
	if (abs(posY1-mAnimationSub->GetPosition().y)>30) {
		mAnimationSub->SetPosition(posX, mAnimationSub->GetPosition().y + 1);	
		mAnimationSub->Update(dt,1);
		return;
	}
	else onDraw = true;
		mAnimation->SetPosition(posX, posY);
		mAnimation->Update(dt,1);

		if (!mAnimationSpawn->mEndAnimate && mAnimation==mAnimationSpawn) {
			return;
		}
		else {
			if (mAnimation != mAnimationRotate) {
				mAnimation = mAnimationRotate;
				this->SetWidth(mAnimationRotate->GetWidth());
				this->SetHeight(mAnimationRotate->GetHeight());
			}	
		}

		Entity::Update(dt);

		if (hp > 15) {
			typeAttack = 1;
		}
		else if (hp > 8) {
			typeAttack = 2;
		}
		else typeAttack = 3;

		if (hp <= 0) {
			isAlive = false;
		}
		
		//kiểm tra va chạm  object với map
		for (size_t j = 0; j < mListMapObject.size(); j++) {

			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
		}

		//Kiểm tra va chạm với nhân vật
		if (mPlayer) {
			//kiểm tra va chạm viên đạn player
			for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
				CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt);
			}
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		}
	}
	
}

void Genjibo::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Door|| other->Tag == EntityTypes::Static) {

		if (side == SideCollisions::Bottom)
			vy = 0;

		if (typeAttack == 1) {	//Chạy qua chạy lại phía dưới
			if (typeAttack == 1) {
				if (side == SideCollisions::Left || side == SideCollisions::Right) {
					vx = -vx;
				}
			}
		}
		else if (typeAttack == 2) //Đi vòng tròn
		{
			if (side == SideCollisions::Left && vy == 0) {
				this->AddPositionX(2);	//Tránh bị xét 2 va chạm ở góc
				vy = -GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Right && vy == 0) {
				this->AddPositionX(-2);
				vy = GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Bottom && vx == 0) {
				this->AddPositionY(-2);
				vx = -GenjiboDefine::SPEED_X;
				vy = 0;

			}
			if (side == SideCollisions::Top && vx == 0) {
				this->AddPositionY(2);
				vx = GenjiboDefine::SPEED_X;
				vy = 0;
			}
		}
		else if (typeAttack == 3) {
			if (vy == 0 && posX < posX1) {
				vy = -GenjiboDefine::SPEED_Y;
			}
			if (side == SideCollisions::Left ) {
				this->AddPositionX(2);
				vy = GenjiboDefine::SPEED_Y;
				vx= GenjiboDefine::SPEED_X;
			}
			if (side == SideCollisions::Right) {
				this->AddPositionX(-2);
				vx = GenjiboDefine::SPEED_X;
			}
			if (side == SideCollisions::Bottom ) {
				this->AddPositionY(-2);
				vy = 0;
			}
			if (side == SideCollisions::Top) {
				this->AddPositionY(2);
				vx=0;
				vy = GenjiboDefine::SPEED_Y;
			}
		}		
	}
	if (other->Tag == EntityTypes::BulletP|| other->Tag == EntityTypes::BulletCharge1|| other->Tag == EntityTypes::BulletCharge2) {
		hp -= other->dame;
		other->Tag = EntityTypes::None;
	}
}

void Genjibo::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		if (onDraw) {
			if (mAnimation == mAnimationSpawn) {
				mSpriteZone->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
			}
				mAnimation->FlipVertical(isFaceRight);
				mAnimation->Draw(transform);
		}
		if (!mAnimationSpawn->mEndAnimate)
			mAnimationSub->Draw(transform);
	}
}
