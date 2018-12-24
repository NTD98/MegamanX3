#include "Escalator.h"


Escalator::Escalator(float posX, float posY, bool isLeftToRight)
{
	mleftToRight = new Animation("Resources/MapObject/Escalator.png", 5, 1, 5, 0.02f);
	mCurrentAnimation = mleftToRight;
	this->SetPosition(posX, posY);
	this->SetWidth(mCurrentAnimation->GetWidth());
	this->SetHeight(mCurrentAnimation->GetHeight());
	mCurrentAnimation->SetPosition(this->GetPosition());
	
	if (isLeftToRight == false) {
		this->Tag = Entity::EntityTypes::EscalatorRTL;
	}
	else {
		this->Tag = Entity::EntityTypes::EscalatorLTR;
	}
}

Escalator::~Escalator()
{
}

void Escalator::Update(float dt)
{
	mCurrentAnimation->Update(dt);
}

void Escalator::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->Draw();
}

void Escalator::OnCollision(Entity * impactor, CollisionReturn data, SideCollisions side)
{

	
}


void Escalator::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->Draw(transform);
}



void Escalator::OnSetPosition(D3DXVECTOR3 poks)
{
	mCurrentAnimation->SetPosition(poks);
}

