#include "ItemsHealth.h"


ItemsHealth::ItemsHealth(float posX, float posY)
{
	mAnimationHealth = new Animation("Resources/MapObject/health.png", 4, 1, 4, 0.1f);
	this->SetPosition(posX, posY);
	mAnimationHealth->SetPosition(this->GetPosition());
	this->SetHeight(mAnimationHealth->GetHeight());
	this->SetWidth(mAnimationHealth->GetWidth());
	this->Tag = Entity::Health;
}

ItemsHealth::~ItemsHealth()
{
}

void ItemsHealth::Update(float dt)
{
	if (this->isAlive == true) {
		mAnimationHealth->Update(dt);
	}
}


void ItemsHealth::OnCollision(Entity * impactor, SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Megaman) {
		this->isAlive = false;
	}
}


void ItemsHealth::Draw(D3DXVECTOR2 transform)
{
	if (this->isAlive == true) {
		mAnimationHealth->Draw(transform);
	}
}


