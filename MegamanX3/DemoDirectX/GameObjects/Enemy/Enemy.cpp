#include "Enemy.h"
#include "GunnerFallingState.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::SetCamera(Camera * camera)
{
	mCamera = camera;
}

void Enemy::Update(float dt)
{
	if (HealthPoint <= 0)
		isAlive = false;
	//?
	if (this->mEnemyData->state->GetState()!=EnemyState::Shooting)
	{
		this->mEnemyData->state->Update(dt);
		mCurrentAnimation->Update(dt);
	}
	else
	{
		this->mEnemyData->state->Update(dt);
		mCurrentAnimation->Update(dt);
	}
	if (this->mEnemyData->state->GetState() != EnemyState::Jumping)
		Jumptime += dt;
	if (this->mEnemyData->state->GetState() != EnemyState::Shooting)
		Shoottime += dt;
	if (this->mEnemyData->state->GetState() == EnemyState::Shooting)
		isdoneAnimation += dt;
	Entity::Update(dt);
}

void Enemy::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
}

void Enemy::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetPosition(D3DXVECTOR3(posX, posY, 0));
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->Draw(D3DXVECTOR2(transform));
}

void Enemy::SetState(EnemyState * newState)
{
	delete this->mEnemyData->state;

	this->mEnemyData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void Enemy::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mEnemyData->state->OnCollision(impactor, side, data);
}

Enemy::MoveDirection Enemy::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

void Enemy::OnNoCollisionWithBottom()
{
	if (mCurrentState != EnemyState::Jumping && mCurrentState != EnemyState::Falling )//&& mCurrentState != EnemyState::Standing)
	{
		this->SetState(new GunnerFallingState(this->mEnemyData));
	}
}

RECT Enemy::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

EnemyState::StateName Enemy::getState()
{
	return mCurrentState;
}

void Enemy::changeAnimation(EnemyState::StateName state)
{
	switch (state)
	{
	case EnemyState::Standing:
		mCurrentAnimation = mAnimationStanding;
		break;

	case EnemyState::Shooting:
		mCurrentAnimation = mAnimationShooting;
		break;
	case EnemyState::Jumping:
		mCurrentAnimation = mAnimationJumping;
		break;
	case EnemyState::Falling:
		mCurrentAnimation = mAnimationShooting;
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

Animation * Enemy::getCurrentAnimation()
{
	return mCurrentAnimation;
}

void Enemy::setjumptime()
{
	this->Jumptime = 0.0f;
}

float Enemy::getjumptime()
{
	return this->Jumptime;
}

void Enemy::setshoottime()
{
	this->Shoottime = 0.0f;
}

float Enemy::getshoottime()
{
	return this->Shoottime;
}

float Enemy::getisdone()
{
	return this->isdoneAnimation;
}

void Enemy::setisdone()
{
	this->isdoneAnimation = 0.0f;
}

void Enemy::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

bool Enemy::GetReverse()
{
	return mCurrentReverse;
}

void Enemy::setJump(bool allowjump)
{
	this->allowjump = allowjump;
}

int Enemy::getHealthPoint()
{
	return HealthPoint;
}
int Enemy::setHealthPoint()
{
	return HealthPoint -= 4;
}
void Enemy::Shooting(D3DXVECTOR3 pos, bool isreverse)
{
}

void Enemy::Standing()
{
}

void Enemy::Jumpping(D3DXVECTOR3 pos)
{
}

void Enemy::Falling()
{
}


EnemyData * Enemy::getEnemydata()
{
	return mEnemyData;
}
