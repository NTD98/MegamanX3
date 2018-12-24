#include "Hornet.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/CollisionManager.h"
#include "../../GameComponents/Sound.h"
Hornet::~Hornet()
{
}

Hornet::Hornet(float posX, float posY, Player* mPlayer, Camera* mCamera)
{
	mAnimationFly = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetFly.txt", 0.02f, true);
	mAnimationStand = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetStand.txt", 0.1f, false);
	mAnimationPrepare = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetPrepare.txt", 0.05f, false);
	mAnimationAttack = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetAttack2.txt", 0.1f, false);
	mAnimationSpawnChild = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetSpawnChild.txt", 0.1f, false);
	mAnimationDie = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetDie.txt", 0.1f, false);

	mAnimation = mAnimationStand;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	this->SetWidth(30);	//người ở giữa
	this->SetHeight(60);	//người ở giữa
	isFaceRight = false;
	isAlive = true;
	isSpawn = true;
	this->mPlayer = mPlayer;
	this->mCamera = mCamera;
	rectMove = mCamera->GetBound();
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
	rectMove.left = 11662;
	rectMove.right = 11939;
	rectMove.top = 3700;
	rectMove.bottom = 3934;
	dame = 1;
	toAttack = true;
	isAttack = false;
	midRectY = rectMove.top + (rectMove.bottom - rectMove.top) / 2;
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mPlayer->hornetHP = new HornetHP(500, 100);

	this->Tag = EntityTypes::HornetBoss;
}

void Hornet::Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject)
{
	if (isAlive)
	{
		mAnimation->Update(dt, 1);
		Entity::Update(dt);

		if (mPlayer->hornetHP->HP <= 0) {
			if (mAnimation != mAnimationDie) {
				mAnimationDie->Start();
				mAnimation = mAnimationDie;
				vy = 200;
			}
		}
		else if (mPlayer->hornetHP->HP > 30) {
			typeAttack = 1;
		}
		else if (mPlayer->hornetHP->HP > 17) {
			typeAttack = 2;
		}
		else {
			typeAttack = 3;
		}
		if (mAnimation == mAnimationAttack) {
			//go to megaman
			if (int(posX) > posMegaX) {
				this->AddPositionX(-2);
			}
			else if (int(posX) < posMegaX) {
				this->AddPositionX(2);
			}
			if (int(posY) > posMegaY) {
				this->AddPositionY(-2);
			}
			else if (int(posY) < posMegaY) {
				this->AddPositionY(2);
			}
			if (int(posY) == posMegaY) {
				mAnimationFly->Start();
				mAnimation = mAnimationFly;
				vy = -HornetDefine::SPEED_Y;
			}
		}
		if (mAnimation->mEndAnimate) {	//Fly->stand->attack->fly
			if (mAnimation == mAnimationStand) {
				if (typeAttack == 1) {
					//Spawn child
					SpawnChild1();

				}
				else if (typeAttack == 2) {

					//prepare go down
					if (toAttack) {
						toAttack = false;
						mAnimationPrepare->Start();
						mAnimation = mAnimationPrepare;
					}
					else {
						toAttack = true;
						SpawnChild1();
					}

				}
				else if (typeAttack == 3) {
					//Spawn child and follow
					SpawnFollow();
				}
			}
			else if (mAnimation == mAnimationSpawnChild) {

				vy = HornetDefine::SPEED_Y;
				if (posX > (mCamera->GetPosition().x)) {
					vx = -HornetDefine::SPEED_X;
				}
				else vx = HornetDefine::SPEED_X;
				mAnimationFly->Start();
				mAnimation = mAnimationFly;
			}
			else if (mAnimation == mAnimationPrepare) {	//done Prepare: Prepare->Attack
				posMegaX = mPlayer->posX;
				posMegaY = rectMove.bottom;
				mAnimationAttack->Start();
				mAnimation = mAnimationAttack;
			}
			else if (mAnimation == mAnimationDie) {
				//isAlive = false;
			}
		}
		if (mAnimation == mAnimationFly) {
			if (posY > rectMove.bottom) {
				this->SetPosition(posX, rectMove.bottom);
				vy = -HornetDefine::SPEED_Y;
			}
			if (posY < rectMove.top) {
				//Stand
				this->SetPosition(posX, rectMove.top);
				mAnimationStand->Start();
				mAnimation = mAnimationStand;
				vy = 0;
				vx = 0;
			}
			if (posX<rectMove.left || posX>rectMove.right) {
				if (posX < rectMove.left) this->SetPosition(rectMove.left, posY);
				if (posX > rectMove.right) this->SetPosition(rectMove.right, posY);
				vy = -HornetDefine::SPEED_Y;
				vx = 0;
			}
		}
		//check collision with megaman
		if (mPlayer) {
			//kiểm tra va chạm viên đạn player
			for (int i = 0; i < mPlayer->bulletlist.size(); i++) {
				CollisionManager::getInstance()->checkCollision(mPlayer->bulletlist[i], this, dt);
			}
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);

			//change flipvertical
			if (mPlayer->posX >= posX) {
				isFaceRight = true;
				direction = 1;
			}
			else {
				isFaceRight = false;
				direction = -1;
			}
		}

		
		for (size_t j = 0; j < mListMapObject.size(); j++) {
			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
		}
		//Update child
		for (int i = 0; i < mListChild.size(); i++) {
			mListChild[i]->Update(dt, mPlayer, mListMapObject);
		}

		//Follow
		if (mAnimationFollow) {
			int xFollow, yFollow, xPlayer, yPlayer;
			xFollow = int(mAnimationFollow->GetPosition().x);
			yFollow = int(mAnimationFollow->GetPosition().y);
			xPlayer = int(mPlayer->posX);
			yPlayer = int(mPlayer->posY);
			if (xFollow < xPlayer) xFollow++;
			else if (xFollow > xPlayer) xFollow--;
			if (yFollow < yPlayer) yFollow++;
			else if (yFollow > yPlayer) yFollow--;

			mAnimationFollow->SetPosition(xFollow, yFollow);
			mAnimationFollow->Update(dt, 1);
			if (xFollow == int(mPlayer->GetPosition().x) && yFollow == int(mPlayer->GetPosition().y)) {
				mPlayer->isFollow = true;
				mAnimationFollow = NULL;
			}
		}
		if (mChildFollow) {
			if (!mChildFollow->isAlive)	mPlayer->isFollow = false;
			if (mPlayer->isFollow) {
				if (int(mChildFollow->posX) < int(mPlayer->posX)) {
					mChildFollow->isFaceRight = false;
					mChildFollow->AddPositionX(1);
				}
				else if (int(mChildFollow->posX) > int(mPlayer->posX)) {
					mChildFollow->isFaceRight = true;
					mChildFollow->AddPositionX(-1);
				}

				//Chạy tới player
				if (int(mChildFollow->posY) < int(mPlayer->posY)) {
					mChildFollow->AddPositionY(1);
				}
				else if (int(mChildFollow->posY) > int(mPlayer->posY)) mChildFollow->AddPositionY(-1);
			}
			mChildFollow->Update(dt, mPlayer, mListMapObject);
		}
	}
	else
	{
		mPlayer->hornetHP = nullptr;
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

void Hornet::OnCollision(Entity * other, SideCollisions side)
{

	if (other->Tag == EntityTypes::BulletP || other->Tag == EntityTypes::BulletCharge1 || other->Tag == EntityTypes::BulletCharge2) {
		mPlayer->hornetHP->AddDame(other->dame);
		other->Tag = EntityTypes::None;
	}
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Static) {
		
		if (mAnimation == mAnimationAttack) {
			mAnimationFly->Start();
			mAnimation = mAnimationFly;
			vy = -HornetDefine::SPEED_Y;
		}
		else
			if (mAnimation == mAnimationDie && side == SideCollisions::Bottom)
			{
				vy = 0;
				vx = 0;
				for (int i = 0; i < 5; i++)
				{
					mExplode[i] = new Animation("Resources/blueexplode.png", 6, 1, 6, 0.1f);
					int X = mAnimation->GetPosition().x;
					int Y = mAnimation->GetPosition().y;
					float ranX = (X - 10) + rand() % (50);
					float ranY = (Y - 10) + rand() % (50);
					mExplode[i]->SetPosition(ranX, ranY);
					isAlive = false;
				}
			}

	}


}

void Hornet::Draw(D3DXVECTOR2 transform)
{
	if (isAlive)
	{
		mAnimation->SetPosition(posX, posY);
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->Draw(transform);
		for (int i = 0; i < mListChild.size(); i++) {
			mListChild[i]->Draw(transform);
		}

		if (mAnimationFollow) {
			mAnimationFollow->Draw(transform);
		}

		if (mChildFollow) {
			mChildFollow->Draw(transform);
		}
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

void Hornet::SpawnChild1()
{
	for (int i = 0; i < mListChild.size(); i++) {
		if (mListChild[i]->isAlive) {
			mListChild[i]->Tag = EntityTypes::HornetChild;
			mListChild[i]->SetPosition(this->GetPosition());
			mAnimationStand->Start();
			mAnimation = mAnimationStand;
			return;
		}
	}
	for (int i = 0; i < mListChild.size(); i++) {
		if (!mListChild[i]->isAlive) {
			mListChild[i] = new ChildHornet(1, posX, posY, direction * 30, -10 + i * 7);
			mListChild[i]->Tag = EntityTypes::HornetChild;
		}
	}
	mAnimationSpawnChild->Start();
	mAnimation = mAnimationSpawnChild;
}

void Hornet::SpawnFollow()
{
	if (toAttack) {
		if (!mChildFollow)
			mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
		if (!mPlayer->isFollow) {
			if (!mChildFollow->isAlive)	mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
			mAnimationFollow = new Animation("Resources/Enemies/Follow.png", "Resources/Enemies/Follow.txt", 0.1f, true);
			mAnimationFollow->SetPosition(posX, posY);
		}
		mAnimationSpawnChild->Start();
		mAnimation = mAnimationSpawnChild;
	}
	else
	{
		if (!mChildFollow)
			mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
		SpawnChild1();
	}
	toAttack = !toAttack;

	//SpawnChild1();
}
