#include "Box.h"


Box::Box(float posX,float posY,int i)
{
	
	mBox2 = new Animation("Resources/MapObject/box2.png", 1, 1, 1, 1.0f);
	mBox22 = new Animation("Resources/MapObject/Box22.png", 1, 1, 1, 1.0f);
	mBoxWall = new Animation("Resources/MapObject/boxWall.png", 1, 1, 1, 1.0f);
	mExplode = new Animation("Resources/explode.png", 6, 1, 6, 0.1f);
	this->posX = posX;
	this->posY = posY;
	ChooseBox(i);
	this->SetWidth(mCurrentAnimation->GetWidth());
	this->SetHeight(mCurrentAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Box;
	this->mCurrentAnimation->SetPosition((this->GetPosition()));
}

void Box::ChooseBox(int i)
{
	switch (i)
	{
	case 0 :
		mCurrentAnimation = mBoxWall;
		this->SetPosition(posX-10, posY -4);
		break;
		break;
	case 2 :
		mCurrentAnimation = mBox2;
		this->SetPosition(posX+7, posY+11.8);
		break;
	case 3 :
		break;
	case 22:
		mCurrentAnimation = mBox22;
		this->SetPosition(posX-11.8, posY-4);
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
			mCurrentAnimation = mExplode;
			mCurrentAnimation->SetPosition(this->GetPosition());
			dtTimeExplode += dt;
		}
		if (dtTimeExplode >= 1.0f) {
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
	if ((impactor->Tag == Entity::BulletP)|| (impactor->Tag == Entity::BulletCharge1) || (impactor->Tag == Entity::BulletCharge2)) {
		this->setHealth(impactor->Tag);
	}
}


void Box::Draw(D3DXVECTOR2 transform)
{
	if (this->isAlive==true) {
		mCurrentAnimation->Draw(transform);
	}
	
}





