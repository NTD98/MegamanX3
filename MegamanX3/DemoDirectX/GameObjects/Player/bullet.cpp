#include "bullet.h"
#include "../../GameComponents/Camera.h"
#include "Player.h"
Bullet::Bullet(D3DXVECTOR3 pos,bool reverse)
{
	bullet = new Animation("Resources/megaman/bullet.png",1,1,1,10);
	destroyedbullet = new Animation("Resources/megaman/destroybullet.png",3,1,3,0.1);
	mChargeBullet1 = new Animation("Resources/megaman/chargedbullet1.png", 6, 1, 6, 0.1);
	mChargeBullet2 = new Animation("Resources/megaman/chargedbullet2.png", 3, 1, 3, 0.1);
	bullet->SetPosition(pos);
	this->vx =0;
	this->SetPosition(bullet->GetPosition().x +bullet->GetImageInfo().Width / 2, bullet->GetPosition().y + bullet->GetImageInfo().Height / 2);
	this->SetWidth(bullet->GetImageInfo().Width);
	this->SetHeight(bullet->GetImageInfo().Height);
	this->Tag = Entity::EntityTypes::BulletP;
	this->isreverse = reverse;
	isdelete = false;
	mCurrentAnimaion = bullet;
}
Bullet::~Bullet()
{
	delete this;
}

void Bullet::Update(float dt, D3DXVECTOR3 pos, bool isreversed)
{
	if (isDone < 0.2f)
	isDone += dt;
	ChangeBulletType(dt);
	mCurrentAnimaion->UpdateS(dt);
	if (!isPressed)
	{
		if (isdelete == false)
		{
			if (isreverse == false)
			{
				mCurrentAnimaion->SetPosition(D3DXVECTOR3(mCurrentAnimaion->GetPosition().x + this->vx*dt + 20, mCurrentAnimaion->GetPosition().y, 0));
				this->SetPosition(mCurrentAnimaion->GetPosition().x, mCurrentAnimaion->GetPosition().y);
			}
			else
			{
				mCurrentAnimaion->SetPosition(D3DXVECTOR3(mCurrentAnimaion->GetPosition().x + this->vx*dt - 20, mCurrentAnimaion->GetPosition().y, 0));
				this->SetPosition(mCurrentAnimaion->GetPosition().x, mCurrentAnimaion->GetPosition().y);
			}
		}
		else
			if (isDone <= 0.2f)
				destroyedbullet->Update(dt);
	}
	else
	{
		mCurrentAnimaion->SetPosition(pos);
		this->isreverse = isreversed;
	}
}

void Bullet::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey,bool isreverse)
{
	if (!isPressed) 
	{
		if (isdelete == false) 
		{
			if (isreverse == false) 
			{
				mCurrentAnimaion->Draw(D3DXVECTOR3(position.x + 2, position.y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
				isreverse = false;
			}
			else
			{
				mCurrentAnimaion->Draw(D3DXVECTOR3(position.x - 2, position.y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
				isreverse = true;
			}
		}
		else
			if (isDone <= 0.2f)
				destroyedbullet->Draw(D3DXVECTOR3(mCurrentAnimaion->GetPosition().x, mCurrentAnimaion->GetPosition().y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
	
}

void Bullet::OnCollision()
{

	D3DXVECTOR3 pos = mCurrentAnimaion->GetPosition();
	//this->bullet->~Sprite();
	destroyedbullet->SetPosition(pos);
	isdelete = true;

}

void Bullet::ChangeBulletType(float dt)
{
	if (isPressed)
	{
		ischarged += dt;
	}
	if (ischarged >= 2.0f)
	{
		mChargeBullet2->SetPosition(mCurrentAnimaion->GetPosition());
		mCurrentAnimaion = mChargeBullet2;
		this->Tag = Entity::EntityTypes::BulletCharge2;
		return;
	}
	if (ischarged >= 1.0f)
	{
		mChargeBullet1->SetPosition(mCurrentAnimaion->GetPosition());
		mCurrentAnimaion = mChargeBullet1;
		this->Tag = Entity::EntityTypes::BulletCharge1;
		return;
	}
}

RECT Bullet::GetBound()
{
	RECT bound;

	bound.left = posX - width / 2;
	bound.right = posX + width / 2;
	bound.top = posY - height / 2;
	bound.bottom = posY + height / 2;

	return bound;
}

void Bullet::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x58])
	{
		isPressed = true;
	}
	else
	{
		isPressed = false;
		ChangeBulletType(0.0f);
	}
}
