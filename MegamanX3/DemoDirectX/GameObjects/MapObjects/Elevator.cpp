#include "Elevator.h"


Elevator::Elevator(D3DXVECTOR3 pos)
{
	mAnimation = new Animation("Resources/MapObject/elevator.png", 2, 1, 2, 0.05f);
	this->SetPosition(pos.x, pos.y);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Elevator;
}

Elevator::~Elevator()
{
}

void Elevator::Update(float dt)
{
	if (this->vy!= 0) {
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->Update(dt);
	}
	if (this->posY > Define::ELEVATOR_POSITION_STOP)  Entity::Update(dt);
	
}

void Elevator::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw();
}

void Elevator::OnCollision(Entity * impactor, CollisionReturn data, SideCollisions side)
{

	if (impactor->Tag == Entity::EntityTypes::Megaman && SideCollisions::Top == side) {
		this->SetVy(Define::ELEVATOR_UP_VELOCITY);
	}
}


void Elevator::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(transform);
}



void Elevator::OnSetPosition(D3DXVECTOR3 poks)
{
	mAnimation->SetPosition(poks);
}

