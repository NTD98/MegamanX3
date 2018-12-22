#include "Box.h"


Box::Box(float posX,float posY,int i)
{
	mBox2 = new Animation("Resources/MapObject/box2.png", 1, 1, 1, 1.0f);
	ChooseBox(i);
	this->SetPosition(posX, posY);
	this->SetWidth(mCurrentAnimation->GetWidth());
	this->SetHeight(mCurrentAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Box;
	this->mCurrentAnimation->SetPosition((this->GetPosition()));
}

void Box::ChooseBox(int i)
{
	switch (i)
	{
	case 1 :
		break;
	case 2 :
		mCurrentAnimation = mBox2;
		break;
	case 3 :
		break;
	default:
		break;
	}
}

void Box::setHealth(Entity::EntityTypes entity)
{
	switch (entity)
	{
	case Entity::EntityTypes::BulletP :
		health -= 4;
		break;
	case Entity::EntityTypes::BulletCharge1:
		health -= 8;
		break;
	case Entity::EntityTypes::BulletCharge2:
		health -= 12;
		break;
	default:
		break;
	}
}

Box::~Box()
{
}

void Box::Update(float dt)
{

	if (this->isAlive == true) {
		if (this->health <= 0) {
			this->isAlive = false;
		}
		mCurrentAnimation->Update(dt);
	}
}



void Box::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->Draw();
}

void Box::OnCollision(Entity * impactor, SideCollisions side)
{
	if (impactor->Tag == (Entity::BulletP || Entity::BulletCharge1 || Entity::BulletCharge2)) {
		this->setHealth(impactor->Tag);
	}
}


void Box::Draw(D3DXVECTOR2 transform)
{
	if (this->isAlive==true) {
		mCurrentAnimation->Draw(transform);
	}
	
}





