﻿#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/Player/PlayerClingingState.h"
#include "../GameObjects/Player/PlayerDeathState.h"

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::generate()
{
	/*Helit* helit = new Helit(176.00, 1932.67);*/
	listhelit.push_back(new Helit(4489.00, 1923.00));
	listhelit.push_back(new Helit(4951.00, 1813.00));
	listhelit.push_back(new Helit(5116.00, 1802.00));
	listhelit.push_back(new Helit(5301.00, 1852.00));
	listhelit.push_back(new Helit(5707.00, 1866.00));
}


void DemoScene::LoadContent()
{
    mBackColor = 0x000000;
    mMap = new GameMap("Resources/Man1_1.tmx");

    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, 
                            mMap->GetHeight() - mCamera->GetHeight());
    mMap->SetCamera(mCamera);
	HealthBar = new Sprite("Resources/megaman/EmptyHealth.png");
	HealthPoint = new Sprite("Resources/megaman/HealthBar.png");
	for (int i = 0; i < 16; i++)
	{
		Health.insert(Health.begin(), 1, HealthPoint);
	}
	mlistGunners = mMap->getEnemy();
    mPlayer = new Player();
	//50/1340
    //mPlayer->SetPosition(90.00, 1854.00);
	

	//BossByte
	mPlayer->SetPosition(8000, 2439);

	//BossGenjibo
	//mPlayer->SetPosition(3100, 2439);

	//BossHornet
	//mPlayer->SetPosition(11120.00, 3926.67);

    mPlayer->SetCamera(mCamera);
	generate();
	mlistdoor = mMap->mlistDoor;
	genjibo = new Genjibo(3750.25, 2403.50);
	byte = new Byte(8836, 2408, mPlayer, mCamera);
	//hornet = new Hornet(11925.33, 3824.67,mPlayer,mCamera);
}

void DemoScene::Update(float dt)
{
	if (mMap->isDaChuyenCanh == false) {
		if (mlistdoor.at(0)->GetBound().left > mCamera->GetBound().right || mlistdoor.at(0)->GetBound().bottom<mCamera->GetBound().top || mlistdoor.at(0)->GetBound().top>mCamera->GetBound().bottom || mlistdoor.at(0)->GetBound().right < mCamera->GetBound().left) {
			//Do nothing
		}
		else {
			if (mlistdoor.at(0)->GetBound().right <= mCamera->GetBound().right) {
				mMap->isStopCamera = true;
				mMap->isDaChuyenCanh = true;
			}
		}
		if (mlistdoor.at(2)->GetBound().left > mCamera->GetBound().right || mlistdoor.at(2)->GetBound().bottom<mCamera->GetBound().top || mlistdoor.at(2)->GetBound().top>mCamera->GetBound().bottom || mlistdoor.at(2)->GetBound().right < mCamera->GetBound().left) {
			//Do nothing
		}
		else {
			if (mlistdoor.at(2)->GetBound().right <= mCamera->GetBound().right) {
				mMap->isStopCamera = true;
				mMap->isDaChuyenCanh = true;
			}
		}
		
	}
	if (mMap->isStopCamera == true && (mlistdoor[0]->isPlayerAfterDoor == true ||  mlistdoor[2]->isPlayerAfterDoor == true )) {
		mMap->isStopCamera = false;
	}
	if (byte) {
		if (byte->GetBound().left > mCamera->GetBound().right || byte->GetBound().bottom<mCamera->GetBound().top || byte->GetBound().top>mCamera->GetBound().bottom || byte->GetBound().right < mCamera->GetBound().left) {
			this->isCollisionVsBossByte = false;
		}
		else {
			this->isCollisionVsBossByte = true;
			byte->Update(dt, mPlayer, this->getMapObject());
		}
	}
		
	if (genjibo) {
		if (genjibo->GetBound().left > mCamera->GetBound().right || genjibo->GetBound().bottom<mCamera->GetBound().top || genjibo->GetBound().top>mCamera->GetBound().bottom || genjibo->GetBound().right < mCamera->GetBound().left) {
			this->isCollisionVsBossgenjibo = false;
		}
		else {
			this->isCollisionVsBossgenjibo = true;
			genjibo->Update(dt, mPlayer, this->getMapObject());
		}
	}
		
	if (hornet) {
		if (hornet->GetBound().left > mCamera->GetBound().right || hornet->GetBound().bottom<mCamera->GetBound().top || hornet->GetBound().top>mCamera->GetBound().bottom || hornet->GetBound().right < mCamera->GetBound().left) {
			this->isCollisionVsBossHornet = false;
		}
		else {
			this->isCollisionVsBossHornet = true;
			hornet->Update(dt, mPlayer, this->getMapObject());
		}
	}
	duration += dt;
	int a = 0;
	for (int i = 0; i < listhelit.size(); i++)
	{
		if (listhelit[i]->GetBound().left > mCamera->GetBound().right || listhelit[i]->GetBound().bottom<mCamera->GetBound().top || listhelit[i]->GetBound().top>mCamera->GetBound().bottom || listhelit[i]->GetBound().right < mCamera->GetBound().left) {
			a++;
			continue;
		}
		this->isCollisionVsHelit = true;
		listhelit.at(i)->Update(dt, mPlayer, this->getMapObject());
	}
	if (a == listhelit.size()) {
		this->isCollisionVsHelit == false;
	}
	if (mPlayer->getState() != PlayerState::Spawning)
		checkCollision();

    mMap->Update(dt);

    mPlayer->HandleKeyboard(keys);

    mPlayer->Update(dt);
	
    CheckCameraAndWorldMap();

	HealthBar->SetPosition(D3DXVECTOR2(mCamera->GetPosition().x - 260, mCamera->GetPosition().y - 200));

	EnemyAction();

	for (int i = 0; i < mlistenemybullets.size(); i++)
		mlistenemybullets.at(i)->Update(dt);
}

void DemoScene::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

	if (mMap->isStopCamera == true) {
		mMap->Draw(mCamera->GetPosition().x/32,mCamera->GetPosition().y/32);
	}
	else {
		mMap->Draw(mPlayer->GetPosition().x / 32, mPlayer->GetPosition().y / 32);
	}

    mPlayer->Draw();
	
	HealthBar->Draw(HealthBar->GetPosition(), RECT(), D3DXVECTOR2(1, 1), trans);
	D3DXVECTOR3 pos;
	for (int i = 0; i <mPlayer->getHealthPoint(); i++)
	{
		if (pos == D3DXVECTOR3())
			pos = D3DXVECTOR3(HealthBar->GetPosition().x, HealthBar->GetPosition().y + 17, 0);
		Health.at(i)->Draw(pos, RECT(), D3DXVECTOR2(1, 1), trans);
		pos = pos + D3DXVECTOR3(0, -4, 0);
	}

	for (int i = 0; i < mlistenemybullets.size(); i++)
		mlistenemybullets.at(i)->Draw(trans);
	if(genjibo && this->isCollisionVsBossgenjibo==true)
		genjibo->Draw(trans);
	if (byte && this->isCollisionVsBossByte==true)
		byte->Draw(trans);
	if (hornet && this->isCollisionVsBossHornet==true)
		hornet->Draw(trans);
	for (int i = 0; i < listhelit.size(); i++)
	{
		listhelit.at(i)->Draw(trans);
	}
}

void DemoScene::EnemyAction()
{
	for (int i = 0; i < mlistGunners.size(); i++)
	{

		if (std::abs(mlistGunners.at(i)->GetPosition().x - mPlayer->GetPosition().x) < 150)
		{
			if (mlistGunners.at(i)->getisdone() >= 0.8f)
				mlistGunners.at(i)->Standing();
			if (mlistGunners.at(i)->getState() != EnemyState::Standing)
				continue;
			if (mlistGunners.at(i)->getshoottime() >= 3.0f&&mlistGunners.at(i)->getisdone() <= 0.8f&&mlistGunners.at(i)->getjumptime() >= 1.0f)
			{
				int direction;
				bool reverse;
				if ((mlistGunners.at(i)->GetPosition().x<mPlayer->GetPosition().x))
					reverse = true;
				else
					reverse = false;
				if (reverse)
					direction = 1;
				else
					direction = -1;
				EnemyBullet* ebullet = new EnemyBullet();
				if (mlistGunners.at(i)->Tag == Entity::EntityTypes::HeadGunner)
				{
					ebullet = new EnemyBullet(1);
					ebullet->Spawn(2, mlistGunners.at(i)->GetPosition().x, mlistGunners.at(i)->GetPosition().y, direction*GunnerDefine::BULLET_SPEED_X_2, -GunnerDefine::BULLET_SPEED_Y_2);
				}
				else if (mlistGunners.at(i)->Tag == Entity::EntityTypes::Gunner)
				{
					ebullet->Spawn(1, mlistGunners.at(i)->GetPosition().x, mlistGunners.at(i)->GetPosition().y - mlistGunners.at(i)->getCurrentAnimation()->GetHeight()/2, direction*GunnerDefine::BULLET_SPEED_X_1, -GunnerDefine::BULLET_SPEED_Y_1);
				}
				else
					EnemyBullet* ebullet = new EnemyBullet();

				mlistenemybullets.push_back(ebullet);
				mlistGunners.at(i)->Shooting(mPlayer->GetPosition(), reverse);
				mlistGunners.at(i)->setisdone();
				mlistGunners.at(i)->setshoottime();

				continue;
			}
			else
				if (mlistGunners.at(i)->getjumptime() >= 3.0f&&mlistGunners.at(i)->getshoottime() >= 2.0f)
				{
					mlistGunners.at(i)->Jumpping(mPlayer->GetPosition());
					mlistGunners.at(i)->setjumptime();
					mlistGunners.at(i)->setisdone();
				}
		}
		else
			if (mlistGunners.at(i)->getisdone() >= 0.8f)
			mlistGunners.at(i)->Standing();

	}
}


void DemoScene::OnKeyDown(int keyCode)
{
    keys[keyCode] = true;

    mPlayer->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;

    mPlayer->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

bool DemoScene::iscolidebullet(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left)
		return false;
	return true;
}



vector<Entity*> DemoScene::getMapObject()
{
		return mapobject;
}

void DemoScene::CheckCameraAndWorldMap()
{
	if (mMap->isStopCamera == true) {
		mCamera->SetPosition(mCamera->GetPosition());
	}
	else {
		vector<Bullet*> bulletlist = mPlayer->getbulletlist();
		mCamera->SetPosition(mPlayer->GetPosition());

		if (mCamera->GetBound().left < 0)
		{
			//vi position cua camera ma chinh giua camera
			//luc nay o vi tri goc ben trai cua the gioi thuc
			mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
		}

		if (mCamera->GetBound().right > mMap->GetWidth())
		{
			//luc nay cham goc ben phai cua the gioi thuc
			mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
				mCamera->GetPosition().y);
		}

		if (mCamera->GetBound().top < 0)
		{
			//luc nay cham goc tren the gioi thuc
			mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
		}

		if (mCamera->GetBound().bottom > mMap->GetHeight())
		{
			//luc nay cham day cua the gioi thuc
			mCamera->SetPosition(mCamera->GetPosition().x,
				mMap->GetHeight() - mCamera->GetHeight() / 2);
		}
		if (bulletlist.size() == 0)
		{

		}
		else
		{
			for (auto it = bulletlist.begin(); it != bulletlist.end();)
			{
				if (bulletlist.at(bulletlist.size() - 1)->GetBound().left > mCamera->GetBound().right || bulletlist.at(bulletlist.size() - 1)->GetBound().right < mCamera->GetBound().left)
				{
					mPlayer->deletebullet();
					break;
				}
				else
				{
					++it;
				}
			}
		}
	}
}

void DemoScene::checkCollision()
{
	int widthBottom = 0;
	D3DXVECTOR2 pos(this->mPlayer->GetPosition().x, this->mPlayer->GetPosition().y);
	vector<Entity*> listCollision;
	vector<Bullet*> bulletlist = mPlayer->getbulletlist();
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
	mapobject = listCollision;
	//player and player's bullet
	// Nếu Đối tượng nào xuất hiện trong camera thì mới tương tác với nhau 
	for (size_t i = 0; i < listCollision.size(); i++)
	{
		//Door vs Player
		for (int j = 0; j < mlistdoor.size(); j++) {
				Entity::CollisionReturn doorVsPlayer = GameCollision::RecteAndRect(mlistdoor.at(j)->GetBound(), this->mPlayer->GetBound());
				Entity::SideCollisions side = GameCollision::getSideCollision(mlistdoor.at(j), doorVsPlayer);
				if (doorVsPlayer.IsCollided) {
					if ((j == 1 && genjibo) || (j == 3 && byte)) {
						this->mPlayer->AddPositionX(-10);
					}
					else {
						if (side == Entity::SideCollisions::Left) {
							mlistdoor.at(j)->isOpenDoor = true;
							if (mlistdoor.at(j)->isPlayerAfterDoor == false) {
								this->mPlayer->isDungYen = true;
							}
							else {
								this->mPlayer->isDungYen = false;
							}
						}
						else {
							this->mPlayer->AddPositionX(10);
						}
					}
			}

			//genjibo vs door
			if (this->isCollisionVsBossgenjibo) {
				Entity::CollisionReturn doorVsGenjibo = GameCollision::RecteAndRect(mlistdoor.at(j)->GetBound(), this->genjibo->GetBound());
				Entity::SideCollisions sidegenjibo = GameCollision::getSideCollision(this->genjibo, doorVsGenjibo);
				if (doorVsGenjibo.IsCollided) {
					this->genjibo->OnCollision(mlistdoor.at(j), sidegenjibo);
				}
			}
		}

		//Helit Vs Player
		if (this->isCollisionVsHelit) {
			for (int j = 0; j < listhelit.size(); j++) {
				Entity::CollisionReturn helitVsPlayer = GameCollision::RecteAndRect(listhelit.at(j)->GetBound(), this->mPlayer->GetBound());
				if (helitVsPlayer.IsCollided) {
					if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
						if (this->mPlayer->isTimeNoDame == false) {
							this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
							if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
								this->mPlayer->setHealthPoint(listhelit.at(j)->Tag, true);
								this->mPlayer->isSetHealth = false;
							}
						}
						if (this->mPlayer->getHealthPoint() <= 0) {
							this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
							this->mPlayer->isBeforeDeath = true;
						}
					}
				}
			}
		}

		//enemy vs static + player
		for (int j = 0; j < mlistGunners.size(); j++)
		{
			int widthBottomE = 0;
			Entity::CollisionReturn g = GameCollision::RecteAndRect(mlistGunners.at(j)->GetBound(), listCollision.at(i)->GetBound());
			if (g.IsCollided)
			{
				Entity::SideCollisions sideEnemy = GameCollision::getSideCollision(mlistGunners.at(j), g);

				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), g);
				if (mlistGunners.at(j)->getState() == EnemyState::Jumping)
					int a = 0;
				mlistGunners.at(j)->OnCollision(listCollision.at(i), g, sideEnemy);
				listCollision.at(i)->OnCollision(mlistGunners.at(j), g, sideImpactor);
				if (sideEnemy == Entity::Bottom || sideEnemy == Entity::BottomLeft
					|| sideEnemy == Entity::BottomRight)
				{
					int bot = g.RegionCollision.right - g.RegionCollision.left;

					if (bot > widthBottomE)
						widthBottomE = bot;
				}
				if (widthBottomE < 8)
					mlistGunners.at(j)->OnNoCollisionWithBottom();
				mlistGunners.at(j)->OnCollision(listCollision.at(i), g, sideEnemy);
			}
			if (mlistGunners[j]->GetBound().left > mCamera->GetBound().right || mlistGunners[j]->GetBound().bottom<mCamera->GetBound().top || mlistGunners[j]->GetBound().top>mCamera->GetBound().bottom || mlistGunners[j]->GetBound().right < mCamera->GetBound().left) {
				continue;
			}
			else {
			Entity::CollisionReturn botVsPlayer = GameCollision::RecteAndRect(mlistGunners.at(j)->GetBound(), mPlayer->GetBound());
				if (botVsPlayer.IsCollided)
				{
					//lay phia va cham cua Entity so voi Player
					Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, botVsPlayer);
					//lay phia va cham cua Player so voi Entity
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mlistGunners.at(j), botVsPlayer);
					if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
						if (this->mPlayer->isTimeNoDame == false) {
							this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
							if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
								this->mPlayer->setHealthPoint(mlistGunners.at(j)->Tag, true);
								this->mPlayer->isSetHealth = false;
							}
						}
						if (this->mPlayer->getHealthPoint() <= 0) {
							this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
							this->mPlayer->isBeforeDeath = true;
						}
					}
				}
			}
		}

		//enemy bullet Vs static + player
		if (mMap->isCollisionVsGunner) {
			for (int j = 0; j < mlistenemybullets.size(); j++)
			{
				Entity::CollisionReturn e = GameCollision::RecteAndRect(mlistenemybullets.at(j)->GetBound(),
					listCollision.at(i)->GetBound());
				Entity::CollisionReturn g = GameCollision::RecteAndRect(mlistenemybullets.at(j)->GetBound(),
					mPlayer->GetBound());


				if (e.IsCollided)
				{
					Entity::SideCollisions sidebullet = GameCollision::getSideCollision(mlistenemybullets.at(j), e);
					mlistenemybullets.at(j)->OnCollision(listCollision.at(i), sidebullet);
					if (mlistenemybullets.at(j)->mExplosion->isEndAnimate)
						mlistenemybullets.erase(mlistenemybullets.begin());
				}
				else
					if (g.IsCollided)
					{
						//lay phia va cham cua Entity so voi Player
						Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, g);

						//lay phia va cham cua Player so voi Entity
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mlistenemybullets.at(j), g);
						if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
							if (this->mPlayer->isTimeNoDame == false) {
								this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
								if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
									this->mPlayer->setHealthPoint(mlistGunners.at(j)->Tag, true);
									this->mPlayer->isSetHealth = false;
								}
							}
							if (this->mPlayer->getHealthPoint() <= 0) {
								this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
								this->mPlayer->isBeforeDeath = true;
							}
						}
					}
			}
		}
		
		//BulletOfPLayerVs...
		for (size_t j = 0; j < bulletlist.size(); j++)
		{
			if (mMap->isCollisionVsGunner) {
 				for (int h = 0; h < mlistGunners.size(); h++) {
					if (mlistGunners[h]->GetBound().left > mCamera->GetBound().right || mlistGunners[h]->GetBound().bottom<mCamera->GetBound().top || mlistGunners[h]->GetBound().top>mCamera->GetBound().bottom || mlistGunners[h]->GetBound().right < mCamera->GetBound().left) {
						continue;
					}
					Entity::CollisionReturn PlayerBulletVsBot = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), mlistGunners.at(h)->GetBound());
					if (PlayerBulletVsBot.IsCollided) {
						mlistGunners.at(h)->setHealthPoint(bulletlist.at(j)->Tag);
						bulletlist.at(j)->OnCollision();
						if (mlistGunners.at(h)->getHealthPoint() <= 0) {
							mlistGunners.at(h)->changeAnimation(EnemyState::Die);
							mlistGunners.at(h)->isAlive = false;
							std::vector<Enemy*>::iterator pos = mlistGunners.begin();
							for (int m = 1; m < h; m++)
								pos++;
							mlistGunners.erase(pos);
						}
					}
				}
			}
			
			if (this->isCollisionVsHelit) {
				for (int h = 0; h < listhelit.size(); h++) {
					if (listhelit[h]->GetBound().left > mCamera->GetBound().right || listhelit[h]->GetBound().bottom<mCamera->GetBound().top || listhelit[h]->GetBound().top>mCamera->GetBound().bottom || listhelit[h]->GetBound().right < mCamera->GetBound().left) {
						continue;
					}
					Entity::CollisionReturn PlayerBulletVsHelit = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), listhelit.at(h)->GetBound());
					if (PlayerBulletVsHelit.IsCollided) {
						bulletlist.at(j)->OnCollision();
						if (listhelit.at(h)->isAlive == false) {
							std::vector<Helit*>::iterator pos = listhelit.begin();
							for (int m = 1; m < h; m++)
								pos++;
							listhelit.erase(pos);
						}
					}
				}
			}
			
			if (this->isCollisionVsBossgenjibo) {
				if (genjibo)
				{
					if (genjibo->GetBound().left > mCamera->GetBound().right || genjibo->GetBound().bottom<mCamera->GetBound().top || genjibo->GetBound().top>mCamera->GetBound().bottom || genjibo->GetBound().right < mCamera->GetBound().left) {
						continue;
					}
					Entity::CollisionReturn ex = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
						genjibo->GetBound());
					if (ex.IsCollided)
					{
						Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(genjibo, ex);
						genjibo->OnCollision(bulletlist.at(j), sidePlayer);
						bulletlist.at(j)->OnCollision();
					}
				}
			}
			
			if (this->isCollisionVsBossByte) {
				if (byte)
				{
					if (byte->GetBound().left > mCamera->GetBound().right || byte->GetBound().bottom<mCamera->GetBound().top || byte->GetBound().top>mCamera->GetBound().bottom || byte->GetBound().right < mCamera->GetBound().left) {
						continue;
					}
					Entity::CollisionReturn ex = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
						byte->GetBound());
					if (ex.IsCollided)
					{
						Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(byte, ex);
						byte->OnCollision(bulletlist.at(j), sidePlayer);
						bulletlist.at(j)->OnCollision();
					}
				}
			}
			
		} 

		//genjiboVs Static
		if (genjibo)
			{
				Entity::CollisionReturn genji = GameCollision::RecteAndRect(genjibo->GetBound(),
					listCollision.at(i)->GetBound());
				if (genji.IsCollided)
				{
					Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(genjibo, genji);

					//lay phia va cham cua Player so voi Entity
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), genji);
					genjibo->OnCollision(listCollision.at(i), sidePlayer);
				}
				if (this->isCollisionVsBossgenjibo) {
					Entity::CollisionReturn genjiVsPlayer = GameCollision::RecteAndRect(genjibo->GetBound(),
						mPlayer->GetBound());
					if (genjiVsPlayer.IsCollided) {
						if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
							if (this->mPlayer->isTimeNoDame == false) {
								this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
								if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
									this->mPlayer->setHealthPoint(Entity::EntityTypes::Genjibo, true);
									this->mPlayer->isSetHealth = false;
								}
							}
							if (this->mPlayer->getHealthPoint() <= 0) {
								this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
								this->mPlayer->isBeforeDeath = true;
							}
						}
					}
				}
			}

		//byte vs player
		if (byte) {
			if (this->isCollisionVsBossByte) {
				Entity::CollisionReturn byteVsPlayer = GameCollision::RecteAndRect(this->byte->GetBound(),
					mPlayer->GetBound());
				if (byteVsPlayer.IsCollided) {
					if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
						if (this->mPlayer->isTimeNoDame == false) {
							this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
							if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
								this->mPlayer->setHealthPoint(Entity::EntityTypes::Byte, true);
								this->mPlayer->isSetHealth = false;
							}
						}
						if (this->mPlayer->getHealthPoint() <= 0) {
							this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
							this->mPlayer->isBeforeDeath = true;
						}
					}
				}
			}
		}
		

		//hornet vs player
		if (hornet) {
			if (this->isCollisionVsBossHornet) {
				Entity::CollisionReturn hornetVsPLayer = GameCollision::RecteAndRect(this->hornet->GetBound(),
					mPlayer->GetBound());
				if (hornetVsPLayer.IsCollided) {
					if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath == false) {
						if (this->mPlayer->isTimeNoDame == false) {
							this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
							if (this->mPlayer->isSetHealth == true || this->mPlayer->getHealthPoint() == 16) {
								this->mPlayer->setHealthPoint(Entity::EntityTypes::HornetBoss, true);
								this->mPlayer->isSetHealth = false;
							}
						}
						if (this->mPlayer->getHealthPoint() <= 0) {
							this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(), pos.x, pos.y));
							this->mPlayer->isBeforeDeath = true;
						}
					}
				}
			}
		}
	
		//PlayerVs Static
		if (listCollision.at(i)->GetBound().left > mCamera->GetBound().right || listCollision.at(i)->GetBound().bottom<mCamera->GetBound().top || listCollision.at(i)->GetBound().top>mCamera->GetBound().bottom || listCollision.at(i)->GetBound().right < mCamera->GetBound().left) {
			continue;
		}
		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollision.at(i)->GetBound());

		if (r.IsCollided)
		{
			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

			//goi den ham xu ly collision cua Player va Entity
			mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
			listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

			if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
				|| sidePlayer == Entity::BottomRight )
			{
				//kiem cha do dai ma mario tiep xuc phia duoi day
				int bot = r.RegionCollision.right - r.RegionCollision.left;

				if (bot > widthBottom)
					widthBottom = bot;
			}
			if ((sidePlayer == Entity::Right || sidePlayer == Entity::Left) && mPlayer->getState() == PlayerState::Jumping)
			{
				//mPlayer->changeAnimation(PlayerState::Clinging);
				mPlayer->SetState(new PlayerClingingState(this->mPlayer->getplayerdata()));
			}
			if (sidePlayer == Entity::Top) {
				
			}
		}
	}

	if (mMap->isStopCamera == true && mPlayer->GetBound().left <= mCamera->GetBound().left) {
		this->mPlayer->AddPositionX(10);
	}

	//Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}