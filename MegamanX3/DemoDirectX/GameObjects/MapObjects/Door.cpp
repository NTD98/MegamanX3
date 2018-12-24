#include "Door.h"

Door::~Door()
{
}

Door::Door(float posX,float posY)
{
	this->mDoorClose = new Animation("Resources/MapObject/doorClose.png", 1, 1, 1, 1.0f);
	this->mDoorClosing = new Animation("Resources/MapObject/doorClosing.png", 16, 1, 16, 0.15f);
	this->mDoorOpen = new Animation("Resources/MapObject/doorOpen.png", 16, 1, 16, 0.15f);
	this->SetPosition(posX, posY);
	this->SetWidth(mDoorClose->GetWidth());
	this->SetHeight(mDoorClose->GetHeight());
	mCurrentAnimation = mDoorClose;
	this->mCurrentAnimation->SetPosition(this->GetPosition());
	this->Tag = Entity::EntityTypes::Door;
}

Door::Door(float posX, float posY, bool isHornet)
{
	this->mDoorClose = new Animation("Resources/MapObject/hornetDoorClose.png", 1, 1, 1, 1.0f);
	this->mDoorClosing = new Animation("Resources/MapObject/hornetDoorClosing.png", 8, 1, 8, 0.15f);
	this->mDoorOpen = new Animation("Resources/MapObject/hornetDoorOpen.png", 8, 1, 8, 0.15f);
	this->SetPosition(posX, posY);
	this->SetWidth(mDoorClose->GetWidth());
	this->SetHeight(mDoorClose->GetHeight());
	mCurrentAnimation = mDoorClose;
	this->mCurrentAnimation->SetPosition(this->GetPosition());
	this->Tag = Entity::EntityTypes::Door;
	this->isDoorHornet = isHornet;
}



void Door::Update(float dt)
{
	if (isOpenDoor == true) {
		mCurrentAnimation = mDoorOpen;
		dtTimeOpen += dt;
	}
	if ((this->isDoorHornet?dtTimeOpen >= 1.2f:dtTimeOpen>=2.4f) && isOpenDoor==true) {
		this->isPlayerAfterDoor = true;
		this->dtPlayerAfterDoor += dt;
	}
	if (dtPlayerAfterDoor >= 1.0f) {
		this->isOpenDoor = false;
		this->isPlayerAfterDoor = false;
		mCurrentAnimation = mDoorClosing;
		dtTimeClosing += dt;
	}
	if (this->isDoorHornet?dtTimeClosing >= 1.2f:dtTimeClosing>=2.4f) {
		mCurrentAnimation = mDoorClose;
		dtTimeClosing = 0;
		dtPlayerAfterDoor = 0;
		dtTimeOpen = 0;
	}
	this->mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Update(dt);
}

void Door::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (this->isPlayerAfterDoor == false) {
		mCurrentAnimation->Draw();
	}
}

void Door::OnCollision(Entity * impactor, CollisionReturn data, SideCollisions side)
{
	
}

void Door::Draw(D3DXVECTOR2 transform)
{
	if (this->isPlayerAfterDoor == false) {
		mCurrentAnimation->Draw(transform);
	}
	
}

void Door::OnSetPosition(D3DXVECTOR3 poks)
{
	mCurrentAnimation->SetPosition(poks);
}
