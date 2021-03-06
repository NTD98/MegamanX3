#include "HeadGunner.h"
#include "HeadGunnerStandingState.h"
#include "HeadGunnerShootingState.h"
#include "HeadGunnerFalling.h"
HeadGunner::HeadGunner(D3DXVECTOR3 pos)
{
	isAlive = true;
	mAnimationStanding = new Animation("Resources/enemy/HeadGunnerStanding.png", 1, 1, 1, 0.3f);
	mAnimationShooting = new Animation("Resources/enemy/HeadGunnerShooting.png", 7, 1, 7, 0.2f);
	SetPosition(pos);
	this->mEnemyData = new EnemyData();
	this->mEnemyData->Enemy = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new HeadGunnerFalling(this->mEnemyData));
	mCurrentAnimation = mAnimationStanding;
	mCurrentAnimation->SetPosition(pos);
	SetWidth(mCurrentAnimation->GetWidth());
	SetHeight(mCurrentAnimation->GetHeight());
	isAlive = true;
	this->HealthPoint = 28;
}

HeadGunner::~HeadGunner()
{
}

void HeadGunner::Shooting(D3DXVECTOR3 pos, bool isreverse)
{
	mCurrentReverse = isreverse;
	mEnemyData->Enemy->SetReverse(isreverse);
	this->SetState(new HeadGunnerShootingState(this->mEnemyData, pos));
}

void HeadGunner::Standing()
{
	this->SetState(new HeadGunnerStandingState(this->mEnemyData));
}
