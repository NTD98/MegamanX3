#include "EnemyBullet.h"
#include "../../GameDefines/GameDefine.h"

EnemyBullet::EnemyBullet()
{
	mSprite1 = new Sprite("Resources/EnemyBullet.png");
 
	this->Tag = EntityTypes::None;
	wasBorn = false;
	typeBullet = 0;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Spawn(int type,float posx, float posy, float vx, float vy)
{
	this->SetPosition(posx,posy);
	this->vx = vx;
	this->vy = vy;
	typeBullet = type;
	if (type == 1) {
		ay = GunnerDefine::BULLET_ACCELERATOR_Y;
		this->SetWidth(mSprite1->GetWidth());
		this->SetHeight(mSprite1->GetHeight());
	}
	wasBorn = true;
	this->Tag = EntityTypes::EnemyBullet;

}

void EnemyBullet::Update(float dt)
{
	if (wasBorn) {
		vy += ay;
		Entity::Update(dt);
	}
	if (mExplosion!=NULL) {
		mExplosion->Update(dt);
	}
}

void EnemyBullet::OnCollision(Entity * other, SideCollisions side)
{
	if (this->Tag != EntityTypes::None) {
		wasBorn = false;
		this->Tag = EntityTypes::None;
	}
}

void EnemyBullet::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn) {
		if (typeBullet == 1) {
			mSprite1->SetPosition(posX, posY);
			mSprite1->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
	}
	if (mExplosion) {
		mExplosion->Draw(transform);
	}
}
