#include "Enemy.h"

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
	if (this->mEnemyData->state)
	{
		this->mEnemyData->state->Update(dt);
	}
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

void Enemy::SetState(EnemyState * newState)
{
	delete this->mEnemyData->state;

	this->mEnemyData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void Enemy::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
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
}

Animation * Enemy::getCurrentAnimation()
{
	return mCurrentAnimation;
}

void Enemy::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

bool Enemy::GetReverse()
{
	return mCurrentReverse;
}

int Enemy::getHealthPoint()
{
	return HealthPoint;
}

EnemyData * Enemy::getEnemydata()
{
	return mEnemyData;
}
