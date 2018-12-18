#include "DeathCircle.h"

DeathCircle::~DeathCircle()
{
}

DeathCircle::DeathCircle(float posX, float posY, float vx, float vy,int NumAnimation)
{
	
	mAnimation1 = new Animation("Resources/megaman/DeathCircle1.png", 1, 1, 1, 0.1f);
	mAnimation2 = new Animation("Resources/megaman/DeathCircle2.png", 1, 1, 1, 0.1f);
	mAnimation3 = new Animation("Resources/megaman/DeathCircle3.png", 1, 1, 1, 0.1f);
	mAnimation4 = new Animation("Resources/megaman/DeathCircle4.png", 1, 1, 1, 0.1f);
	mAnimation5 = new Animation("Resources/megaman/DeathCircle5.png", 1, 1, 1, 0.1f);
	
	this->SetPosition(posX, posY);
	posX1 = posX;
	posY1 = posY;
	this->vx = vx;
	this->vy = vy;
	switch (NumAnimation)
	{
	case 1:
		mCurrentAnimation = mAnimation1;
		break;
	case 2:
		mCurrentAnimation = mAnimation2;
		break;
	case 3:
		mCurrentAnimation = mAnimation3;
		break;
	case 4:
		mCurrentAnimation = mAnimation4;
		break;
	case 5:
		mCurrentAnimation = mAnimation5;
		break;
	default:
		break;
	}
}

void DeathCircle::Update(float dt)
{
	Entity::Update(dt);
}

void DeathCircle::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetPosition(posX, posY);
	mCurrentAnimation->Draw(transform);
}
