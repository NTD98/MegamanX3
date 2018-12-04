#include "bullet.h"
#include "../../GameComponents/Camera.h"
#include "Player.h"
Bullet::Bullet(D3DXVECTOR3 pos,bool reverse)
{
	bullet = new Sprite("Resources/megaman/bullet.png");
	destroyedbullet = new Animation("Resources/megaman/destroybullet.png",3,1,3,0.2);
	bullet->SetPosition(pos);
	this->vx =0;
	this->SetPosition(bullet->GetPosition().x + bullet->GetImageInfo().Width / 2, bullet->GetPosition().y + bullet->GetImageInfo().Height / 2);
	this->SetWidth(bullet->GetImageInfo().Width);
	this->SetHeight(bullet->GetImageInfo().Height);
	this->Tag = Entity::EntityTypes::BulletP;
	this->isreverse = reverse;
	isdelete = false;
}
Bullet::~Bullet()
{
	delete this;
}

void Bullet::Update(float dt)
{
	if(isDone<0.6f)
	isDone += dt;
	if (isdelete == false)
	{
		if (isreverse == false)
		{
			bullet->SetPosition(D3DXVECTOR3(bullet->GetPosition().x + this->vx*dt + 20, bullet->GetPosition().y, 0));
			this->SetPosition(bullet->GetPosition().x, bullet->GetPosition().y);
		}
		else
		{
			bullet->SetPosition(D3DXVECTOR3(bullet->GetPosition().x + this->vx*dt - 20, bullet->GetPosition().y, 0));
			this->SetPosition(bullet->GetPosition().x, bullet->GetPosition().y);
		}
	}
	else
		if(isDone<=0.6f)
			destroyedbullet->Update(dt);
}

void Bullet::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (isdelete==false)
	{
		if (isreverse == false)
		{
			bullet->Draw(D3DXVECTOR3(bullet->GetPosition().x + 2, bullet->GetPosition().y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
			isreverse = false;
		}
		else
		{
			bullet->Draw(D3DXVECTOR3(bullet->GetPosition().x - 2, bullet->GetPosition().y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
			isreverse = true;
		}
	}
	else
		if(isDone<=0.6f)
		destroyedbullet->Draw(D3DXVECTOR3(bullet->GetPosition().x, bullet->GetPosition().y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Bullet::OnCollision()
{

	D3DXVECTOR3 pos = bullet->GetPosition();
	//this->bullet->~Sprite();
	destroyedbullet->SetPosition(pos);
	isdelete = true;
	destroyedbullet->Draw();
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
