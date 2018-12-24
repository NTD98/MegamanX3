#include "Genjibo.h"
#include "../../Scenes/DemoScene.h"
#include "../../GameComponents/CollisionManager.h"
#include "../../GameComponents/Sound.h"
Genjibo::~Genjibo()
{
}

Genjibo::Genjibo(float posX, float posY)
{
	mAnimationSpawn = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboSpawn.txt", 0.05f, false);
	mAnimationRotate = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboRotateLeft.txt", 0.001f, true);
	mAnimationSub = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/SubGenjibo.txt", 0.01f, false);
	mAnimationCircle = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboCircle.txt", 0.01f, true);
	mAnimationDie = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboDie.txt", 0.01f, false);
	mSpriteZone = new Sprite("Resources/Boss/GenjiboZone.png");

	mAnimation = mAnimationSpawn;
	isFaceRight = false;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	mSpriteZone->SetPosition(posX, posY - 5);
	mAnimationSub->SetPosition(posX, posY - 200);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());

	posX1 = posX;
	posY1 = posY;
	hp = 30;
	vx = 100;
	vy = 20;
	dame = 2;
	isAlive = true;
	isSpawn = true;
	onDraw = false;
	typeAttack = 0;
	this->Tag = EntityTypes::Genjibo;
	isChange = false;
}

void Genjibo::Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject)
{
	if (isAlive)
	{
		if (typeAttack == 2)
			type2 += dt;
		else
			if (typeAttack == 4)
				type4 += dt;
		if (isAlive) {
			//Con ong bay xuống
			if (abs(posY1 - mAnimationSub->GetPosition().y) > 30) {
				mAnimationSub->SetPosition(posX, mAnimationSub->GetPosition().y + 1);
				mAnimationSub->Update(dt, 1);
				return;
			}
			else onDraw = true;
			mAnimation->SetPosition(posX, posY);
			mAnimation->Update(dt, 1);

			if (!mAnimationSpawn->mEndAnimate && mAnimation == mAnimationSpawn) {
				return;
			}
			else {
				if (typeAttack == 4 && !isChange)
				{
					mAnimationCircle->SetPosition(mAnimation->GetPosition());
					mAnimation = mAnimationCircle;
					this->SetWidth(mAnimationCircle->GetWidth());
					this->SetHeight(mAnimationCircle->GetHeight());
					isChange = true;
				}
				else
					if (mAnimation != mAnimationRotate) {
						if (typeAttack != 4)
						{
							mAnimation = mAnimationRotate;
							this->SetWidth(mAnimationRotate->GetWidth());
							this->SetHeight(mAnimationRotate->GetHeight());
						}
					}
			}

			Entity::Update(dt);

			if (hp > 25) {
				typeAttack = 1;
			}
			else if (hp > 18) {
				typeAttack = 2;
			}
			else
				if (hp > 10)
				{
					typeAttack = 3;
				}
				else
				{
					typeAttack = 4;
				}
			if (hp <= 0) {
				isAlive = false;
			}

			////kiểm tra va chạm  object với map
			//for (size_t j = 0; j < mListMapObject.size(); j++) {

			//	CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
			//}
			if (type2 >= 0.5f&&check2&&typeAttack == 2)
			{
				vy = -vy;
				type2 = 0.0f;
				check2 = false;
			}
			else
				if (type4 >= 0.5&&typeAttack == 4)
				{
					vy = -vy;
					type4 = 0.0f;
				}

			////Kiểm tra va chạm với nhân vật
			//if (mPlayer) {
			//	//kiểm tra va chạm viên đạn player
			//	for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
			//		CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt);
			//	}
			//	CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
			//}
		}
	}
	else
	{
		if (mExplode[count])
		{
			Sound::getInstance()->play("explosion", false, 1);
			if (!mExplode[count]->isEndAnimate)
				mExplode[count]->UpdateS(dt);
			else
				mExplode[count] = nullptr;
		}
		if (mExplode[4])
			if (mExplode[4]->isEndAnimate)
				mAnimation = nullptr;
	}
}

void Genjibo::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Door || other->Tag == EntityTypes::Static) {

		if (side == SideCollisions::Bottom)
			vy = 0;

		if (typeAttack == 1) {	//Chạy qua chạy lại phía dưới
			if (typeAttack == 1) {
				if (side == SideCollisions::Left || side == SideCollisions::Right) {
					vx = -vx;
				}
			}
		}
		else if (typeAttack == 3) //Đi vòng tròn
		{
			if (side == SideCollisions::Left && vy == 0) {
				this->AddPositionX(2);	//Tránh bị xét 2 va chạm ở góc
				vy = -GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Right && vy == 0) {
				this->AddPositionX(-2);
				vy = GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Bottom && vx == 0) {
				this->AddPositionY(-2);
				vx = -GenjiboDefine::SPEED_X;
				vy = 0;

			}
			if (side == SideCollisions::Top && vx == 0) {
				this->AddPositionY(2);
				vx = GenjiboDefine::SPEED_X;
				vy = 0;
			}
		}
		else if (typeAttack == 2) {
			if (side == SideCollisions::Left) {
				vy = -GenjiboDefine::SPEED_Y;
				vx = GenjiboDefine::SPEED_X;
				type2 = 0.0f;
				check2 = true;
			}
			if (side == SideCollisions::Top)
			{
				vy = -vy;
			}
			if (side == SideCollisions::Bottom) {
				this->AddPositionY(-2);
				vy = 0;
				check2 = false;

			}
			if (side == SideCollisions::Right) {
				this->AddPositionX(-2);
				vx = -GenjiboDefine::SPEED_X;
			}
		}
		else
		{
			if (side == SideCollisions::Left) {
				vy = -GenjiboDefine::SPEED_Y;
				vx = GenjiboDefine::SPEED_X;
				type4 = 0.0f;
			}
			if (side == SideCollisions::Top)
			{
				vy = -vy;
			}
			if (side == SideCollisions::Bottom) {
				this->AddPositionY(-2);
				if (vy != 0)
					vy = -vy;
				else
					vy = -GenjiboDefine::SPEED_Y;
			}
			if (side == SideCollisions::Right) {
				vy = -GenjiboDefine::SPEED_Y;
				vx = -GenjiboDefine::SPEED_X;
				this->AddPositionX(-2);
			}
		}
	}
	if (other->Tag == EntityTypes::BulletP || other->Tag == EntityTypes::BulletCharge1 || other->Tag == EntityTypes::BulletCharge2) {
		hp -= other->dame;
		other->Tag = EntityTypes::None;
		if (hp <= 0)
		{
			if (mAnimation != mAnimationDie)
			{
				mAnimationDie->SetPosition(mAnimation->GetPosition());
				mAnimation = mAnimationDie;
			}
			for (int i = 0; i < 5; i++)
			{
				mExplode[i] = new Animation("Resources/blueexplode.png", 6, 1, 6, 0.1f);
				int X = mAnimation->GetPosition().x;
				int Y = mAnimation->GetPosition().y;
				float ranX = (X - 10) + rand() % (50);
				float ranY = (Y - 10) + rand() % (50);
				mExplode[i]->SetPosition(ranX, ranY);
			}
			vx = 0;
			vy = 0;
		}
	}
}

void Genjibo::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		if (onDraw) {
			if (mAnimation == mAnimationSpawn) {
				mSpriteZone->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
			}
			mAnimation->FlipVertical(isFaceRight);
			mAnimation->Draw(transform);
		}
		if (!mAnimationSpawn->mEndAnimate)
			mAnimationSub->Draw(transform);
	}
	if (mExplode[count])
	{
		if (!mExplode[count]->isEndAnimate)
		{
			mExplode[count]->Draw(transform);
		}
		else
		{
			if (count<4)
				count++;
		}
	}
}
