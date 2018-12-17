#include "DeathCircle.h"

DeathCircle::~DeathCircle()
{
}

DeathCircle::DeathCircle(float posX, float posY, float vx, float vy)
{
	mAnimation = new Animation("Resources/megaman/DeathCircle.png", 1, 1, 1, 1);
	this->SetPosition(posX, posY);
	posX1 = posX;
	posY1 = posY;
	this->vx = vx;
	this->vy = vy;
}

void DeathCircle::Update(float dt)
{

	Entity::Update(dt);
}

void DeathCircle::Draw(D3DXVECTOR2 transform)
{
	mAnimation->SetPosition(posX, posY);
	mAnimation->Draw(transform);
}
