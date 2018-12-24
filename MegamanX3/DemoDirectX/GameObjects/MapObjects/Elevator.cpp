#include "Elevator.h"


Elevator::Elevator(float posX,float posY,bool Elevator2)
{
	mAnimation = new Animation("Resources/MapObject/elevator.png", 2, 1, 2, 0.1f);
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	mAnimation->SetPosition(this->GetPosition());
	this->Tag = Entity::EntityTypes::Elevator;
	if (Elevator2 == true) {
		this->isElevator2 = true;
	}
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
	if (this->isElevator2 == true) {
		//posY Giam
		if (this->posY > Define::ELEVATOR2_POSITION_STOP)  Entity::Update(dt);
	}
	else {
		if (this->posY > Define::ELEVATOR_POSITION_STOP)  Entity::Update(dt);
	}
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

