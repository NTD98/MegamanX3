#include "Helit.h"
#include "../../GameComponents/CollisionManager.h"
#include "../../GameDefines/GameDefine.h"
Helit::~Helit()
{
}

Helit::Helit(float posX, float posY)
{
	mAnimation = new Animation("Resources/enemy/helit1.png",5,1,5, 0.1f);
	
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Helit;
	isFaceLeft = true;
	//mGameMap = map;
	hp = 16;
	isAlive = true;
	isSpawn = true;
	direction = -1;
	iBullet = 0;
	posX1 = posX;
	posY1 = posY;
	//Bullet
	mBullet = new EnemyBullet(1);
}

void Helit::Update(float dt,Player* mPlayer, vector<Entity*> mListEntity)
{
	if (isAlive) {
		//kiểm tra va chạm viên đạn player
		this->SetWidth(mAnimation->GetWidth());
		this->SetHeight(mAnimation->GetHeight());
		for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
			CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt / 1000);
		}
		if (hp <= 0) {
			Die();
			return;
		}
		if (posY <= posY1 && vy<0) {
			vy = 0;
		}
		if (abs(posX - mPlayer->posX) < 100 && abs(posY - mPlayer->posY)<100)	// khoảng cách dưới 100
		{
			if (mPlayer->posX < posX)	//bên trái
			{
				isFaceRight = false;
				direction = -1;
			}
			else
			{		//bên phải
				isFaceRight = true;
				direction = 1;
			}
			if ( vy==0) {
				vy = HelitDefine::SPEED_Y;
			}
			if (posY > mPlayer->posY && vy>0) {
				vy = 0; 
				if (!mBullet->wasBorn || abs(mBullet->posX-posX)>200) {
					mBullet->Spawn(2, this->posX, this->posY, direction*HelitDefine::BULLET_SPEED_X,HelitDefine::BULLET_SPEED_Y);
					vy = -HelitDefine::SPEED_Y;
				}
			}
		}
		
		mAnimation->Update(dt);
		Entity::Update(dt);
	}
		////Kiểm tra va chạm

		mBullet->Update(dt);
		
		CollisionManager::getInstance()->checkCollision(mPlayer, mBullet, dt );

		for (int j = 0; j < mListEntity.size(); j++)
			if (mListEntity[j] != this)
				CollisionManager::getInstance()->checkCollision(mListEntity[j], mBullet, dt);

	
	if (explosion) {
		explosion->Update(dt);
	}
}


void Helit::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		switch (other->Tag)
		{
		case Entity::EntityTypes::BulletP :
			hp -= 4;
			break;
		case Entity::EntityTypes::BulletCharge1:
			hp -= 10;
			break;
		case Entity::EntityTypes::BulletCharge2:
			hp -= 20;
			break;
		default:
			break;
		}
		other->Tag = EntityTypes::None;
		return;
	}
}

void Helit::Draw(D3DXVECTOR2 transform)
{
	mBullet->Draw(transform);
	if (isAlive) {
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->Draw(transform);
	}
	if (explosion)
		explosion->Draw(transform);
}

void Helit::Die()
{
	if (isAlive) {
		this->Tag = EntityTypes::None;
		explosion = new Animation("Resources/explode.png",6,1,6,0.1);
		isAlive = false;
	}
}
