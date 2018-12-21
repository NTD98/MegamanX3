#include "Byte.h"
#include "../../GameComponents/CollisionManager.h"
#include "../../GameDefines/GameDefine.h"

Byte::~Byte()
{

}

Byte::Byte(float posX, float posY,Player* mPlayer,Camera* mCamera)
{
	mAnimationStanding = new Animation("Resources/Boss/bytestand.png", 1, 1, 1, 1.0f);
	mAnimationDying = new Animation("Resources/Boss/blueexplode.png", 6, 1, 6, 0.1f);
	mAnimation = mAnimationStanding;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	vx = 0;
	vy = 0;
	dame = 2;
	isAlive = true;
	isSpawn = true;
	isshoot = true;
	isslide = false;
	onDraw = false;
	right = false;
	this->mPlayer = mPlayer;
	typeAttack = 0;
	this->hp = 40;
	this->Tag = EntityTypes::Byte;
	mPlayer->byteHP = new HornetHP(mCamera->GetPosition().x + 200, mCamera->GetPosition().y + 100);
}

void Byte::Update(float dt, Player * mPlayer, vector<Entity*> mListMapObject)
{
	if(this->hp<=0)
	{
		isAlive = false;
		mAnimation = mAnimationDying;
		mPlayer->byteHP = nullptr;
	}
	mAnimation->UpdateS(dt);
	delay += dt;
	if (isAlive)
	{
		if (abs(mPlayer->GetPosition().x - mAnimation->GetPosition().x) < 800)
		{
			if (mAnimation == mAnimationStanding)
			{
				if (delay >= 4.0f)
				{
					Shoot();
					delay = 0.0f;
				}
			}
			else
				if (mAnimation == mAnimationShooting)
					if (mAnimation->isEndAnimate)
					{
						Slide();
						if (right)
							vx = 300;
						else
							vx = -300;
					}
		}

		for (size_t j = 0; j < mListMapObject.size(); j++) {
			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
			if (bomp)
				CollisionManager::getInstance()->checkCollision(bomp, mListMapObject[j], dt);
		}
		if (bomp)
			CollisionManager::getInstance()->checkCollision(bomp, this, dt);
		//Kiểm tra va chạm với nhân vật
		if (mPlayer) {
			//kiểm tra va chạm viên đạn player
			for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
				CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt);
			}
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		}
		Entity::Update(dt);
		mAnimation->SetPosition(posX, posY);
		if (bomp)
		{
			bomp->Update(dt);
		}
	}
}

void Byte::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Door || other->Tag == EntityTypes::Static)
	{
		if (side == SideCollisions::Left || side == SideCollisions::Right) {
			vx = -vx;
			if (mAnimation == mAnimationSlidding)
			{
				if (mAnimation->isEndAnimate)
				{
					if (side == SideCollisions::Left)
					{
						vx = 0;
						Stand();
						right = true;
					}
					else
					{
						vx = 0;
						Stand();
						this->SetPosition(posX-5, posY);
						right = false;
					}
				}
			}
		}
	}
	if (other->Tag == EntityTypes::Bomps)
	{
		vx = -vx;
		if (mAnimation == mAnimationSlidding)
		{
			if (mAnimation->isEndAnimate)
			{
				if (side == SideCollisions::Left)
				{
					vx = 0;
					Stand();
					right = true;
				}
				else
				{
					vx = 0;
					Stand();
					this->SetPosition(posX - 5, posY);
					right = false;
				}
			}
		}
	}
	if (other->Tag == EntityTypes::BulletP || other->Tag == EntityTypes::BulletCharge1 || other->Tag == EntityTypes::BulletCharge2) {
		hp -= other->dame;
		mPlayer->byteHP->AddDame(other->dame);
		other->Tag = EntityTypes::None;
	}

}

void Byte::Shoot()
{
	mAnimationShooting = new Animation("Resources/Boss/byteshoot.png", 5, 1, 5, 0.2f);
	vx = 0;
	mAnimationShooting->SetPosition(mAnimation->GetPosition());
	mAnimation = mAnimationShooting;
	if(!right)
		bomp = new Bomp(mAnimation->GetPosition()+D3DXVECTOR3(-mAnimation->GetWidth()/2-10,0,0),right);
	else
		bomp = new Bomp(mAnimation->GetPosition() + D3DXVECTOR3(mAnimation->GetWidth() / 2 + 10, 0, 0), right);
}

void Byte::Slide()
{
	mAnimationSlidding = new Animation("Resources/Boss/byteslide.png", 3, 1, 3, 0.2f);
	mAnimationSlidding->SetPosition(mAnimation->GetPosition());
	mAnimation = mAnimationSlidding;
}

void Byte::Stand()
{
	mAnimationStanding->SetPosition(mAnimation->GetPosition());
	mAnimation = mAnimationStanding;
}

void Byte::Draw(D3DXVECTOR2 transform)
{
	if (isAlive)
	{
		mAnimation->FlipVertical(right);
		if (mAnimation)
			mAnimation->Draw(transform);
		if (bomp)
			if (!bomp->isdestoyed)
			{
				bomp->Draw(transform);
			}
	}
}
