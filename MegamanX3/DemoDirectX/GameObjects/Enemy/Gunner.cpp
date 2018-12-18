#include "Gunner.h"
#include "GunnerStandingState.h"
#include "GunnerShootingState.h"
#include "GunnerJumpingState.h"
#include "GunnerFallingState.h"
Gunner::Gunner(D3DXVECTOR3 pos)
{
	isAlive = true;
	mAnimationStanding = new Animation("Resources/enemy/GunnerStanding.png",2,1,2,0.3f);
	mAnimationShooting = new Animation("Resources/enemy/GunnerShooting.png", 4, 1, 4, 0.2);
	mAnimationJumping = new Animation("Resources/enemy/GunnerJumping.png", 2, 1, 2, 0.5f);
	mAnimationShooting = new Animation("Resources/enemy/GunnerShooting.png", 4, 1, 4, 0.2f);
	SetPosition(pos);
	this->mEnemyData = new EnemyData();
	this->mEnemyData->Enemy = this;
	this->vx = 0;
	this->vy = 0;
	//this->SetState(new GunnerFallingState(this->mEnemyData));
	this->SetState(new GunnerStandingState(this->mEnemyData));
	mCurrentAnimation = mAnimationStanding;
	mCurrentAnimation->SetPosition(pos);
    SetWidth(mCurrentAnimation->GetWidth());
	SetHeight(mCurrentAnimation->GetHeight());
	isAlive = true;
	this->HealthPoint = 16;
}

Gunner::~Gunner()
{
	delete this;
}

void Gunner::Shooting(D3DXVECTOR3 pos,bool isreverse)
{
	mCurrentReverse = isreverse;
	mEnemyData->Enemy->SetReverse(isreverse);
	this->SetState(new GunnerShootingState(this->mEnemyData,pos));
}

void Gunner::Standing()
{
	this->SetState(new GunnerStandingState(this->mEnemyData));
	allowjump = true;
}

void Gunner::Jumpping(D3DXVECTOR3 pos)
{
	if (allowjump)
	{
		this->SetState(new GunnerJumpingState(this->mEnemyData, pos));
		allowjump = false;
	}
}

void Gunner::Falling()
{
	this->SetState(new GunnerFallingState(this->mEnemyData));
}



