#include "bomp.h"
#include "../../GameComponents/Sound.h"
Bomp::Bomp(D3DXVECTOR3 pos,bool reverse)
{
	flybomp = new Animation("Resources/Boss/bompfly.png", 2, 1, 2, 0.1f);
	clingbomp = new Animation("Resources/Boss/bompcling.png", 3, 1, 3, 0.1f);
	destroyedbomp = new Animation("Resources/explode.png", 6, 1, 6, 0.1f);
	isreverse = reverse;
	bomp = flybomp;
	bomp->SetPosition(pos);
	if (isreverse)
		vx = 300;
	else
		vx = -300;
	vy = 0;
	this->SetPosition(pos);
	this->Tag = EntityTypes::Bomps;
	isdestoyed = false;
}

Bomp::~Bomp()
{
	delete this;
}

void Bomp::Draw(D3DXVECTOR2 transform)
{
	bomp->FlipVertical(isreverse);
	bomp->Draw(transform);
}

void Bomp::Update(float dt)
{
	if (bomp == destroyedbomp|| bomp == clingbomp)
	{
		bomp->UpdateS(dt);
		if(bomp == destroyedbomp)
			if (bomp->isEndAnimate)
				isdestoyed = true;
	}
	else
		bomp->Update(dt);

	Entity::Update(dt);
	bomp->SetPosition(posX, posY);
}

void Bomp::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Door || other->Tag == EntityTypes::Static)
	{
		if (bomp == flybomp)
		{
			clingbomp->SetPosition(bomp->GetPosition());
			bomp = clingbomp;
			vx = 0;
		}
	}
	if (other->Tag == EntityTypes::Byte)
	{
		if (bomp == clingbomp)
		{
			Sound::getInstance()->play("explosion", false, 1);
			destroyedbomp->SetPosition(bomp->GetPosition());
			bomp = destroyedbomp;
		}
	}
}
