#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/Player/PlayerClingingState.h"
#include "../GameObjects/Player/PlayerDeathState.h"
#include "../GameComponents/Sound.h"
DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::generate()
{
	/*Helit* helit = new Helit(176.00, 1932.67);*/
	listhelit.push_back(new Helit(4450.00, 1890));
	listhelit.push_back(new Helit(5116.00, 1870));
	listhelit.push_back(new Helit(5707.00, 1850));

	mlistdoor.push_back(new Door(3490.33, 2424.67));
	mlistdoor.push_back(new Door(3860.96, 2424.67));
	mlistdoor.push_back(new Door(8520.78, 2424.67));
	mlistdoor.push_back(new Door(8893.44, 2424.67));
	//door hornet
	mlistdoor.push_back(new Door(11620, 3923.67, true));

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


	changeBulletEffect = new ChangeBulletEffect();
	for (int i = 0; i < 16; i++)
	{
		Health.insert(Health.begin(), 1, HealthPoint);
	}
	mlistGunners = mMap->getEnemy();
	mlistBox = mMap->getBox();
	mlistElevator = mMap->mlistElevator;
	mlistEscalator = mMap->mlistEscalator;
	mlisItemHealth = mMap->mlistHealth;
    mPlayer = new Player();
	//50/1340
    mPlayer->SetPosition(90.00, 1854.00);
	
	//healtItem
	//mPlayer->SetPosition(5171.33, 3398.67);

	//elevator1
	//mPlayer->SetPosition(1100, 1700);

	//helit
	//mPlayer->SetPosition(4500, 2400);

	//BossByte
	//mPlayer->SetPosition(8000, 2439);

	//BossGenjibo
	//mPlayer->SetPosition(3100, 2439);

	//BossHornet
	//mPlayer->SetPosition(11110, 3926);

	//esclator
	//mPlayer->SetPosition(2469.33, 904.67);
	Sound::getInstance()->loadSound("Resources/Sound/Background.wav", "background");
	Sound::getInstance()->loadSound("Resources/Sound/Explosion.wav", "explosion");
	Sound::getInstance()->play("background", true, 0);
    mPlayer->SetCamera(mCamera);
	generate();
	
	
	
}



void DemoScene::Update(float dt)
{
	if (!hornet && this->mPlayer->GetBound().left>mlistdoor.at(4)->GetBound().right) {
		{
			this->mPlayer->changeAnimation(PlayerState::Win);
		}
	}
	if ((this->mPlayer->GetBound().left > mlistdoor.at(1)->GetBound().right && this->isInCamera(mlistdoor.at(1)) )|| (this->mPlayer->GetBound().left > mlistdoor.at(3)->GetBound().right && this->isInCamera(mlistdoor.at(3))) ) {
		mMap->isDaChuyenCanh = false;
	}

	if ((this->mPlayer->GetBound().left > mlistdoor.at(0)->GetBound().right) && this->isBossGenJiboAcceptSpawn==false) {
		genjibo = new Genjibo(3750.25, 2403.50);
		this->isBossGenJiboAcceptSpawn = true;
	}
	if ((this->mPlayer->GetBound().left > mlistdoor.at(2)->GetBound().right) && this->isBossByteAcceptSpawn == false) {
		byte = new Byte(8834, 2408, mPlayer, mCamera);
		this->isBossByteAcceptSpawn = true;
	}
	if ((this->mPlayer->GetBound().left > mlistdoor.at(4)->GetBound().right) && this->isBossHornetAcceptSpawn == false) {
		hornet = new Hornet(11925.33, 3824.67, mPlayer, mCamera);
		this->isBossHornetAcceptSpawn = true;
	}
	
	if (mMap->isDaChuyenCanh == false) {
		if (this->isInCamera(mlistdoor.at(0)) == false) {
			//Do nothing
		}
		else {
			if (mlistdoor.at(0)->GetBound().right <= mCamera->GetBound().right) {
				mMap->isStopCamera = true;
				mMap->isDaChuyenCanh = true;
			}
		}
		if (this->isInCamera(mlistdoor.at(2)) == false) {
			//Do nothing
		}
		else {
			if (mlistdoor.at(2)->GetBound().right <= mCamera->GetBound().right) {
				mMap->isStopCamera = true;
				mMap->isDaChuyenCanh = true;
			}
		}
		if (this->isInCamera(mlistdoor.at(4)) == false) {
			//Do nothing
		}
		else {
			if (mlistdoor.at(4)->GetBound().right <= mCamera->GetBound().right) {
				mMap->isStopCamera = true;
				mMap->isDaChuyenCanh = true;
			}
		}
		
	}
	if (mMap->isStopCamera == true && (mlistdoor[0]->isPlayerAfterDoor == true ||  mlistdoor[2]->isPlayerAfterDoor == true || mlistdoor[4]->isPlayerAfterDoor==true )) {
		mMap->isStopCamera = false;
	}

	if (byte) {
		if (this->isInCamera(byte) == true) {
			this->isCollisionVsBossByte = true;
			byte->Update(dt, mPlayer, this->getMapObject());
		}
		else {
			this->isCollisionVsBossByte = false;
		}
		if (byte->mExplode[4])
			if (byte->mExplode[4]->isEndAnimate)
			{
				byte = nullptr;
				isCollisionVsBossByte = false;
			}
	}
		
	if (genjibo) {
		if (this->isInCamera(genjibo) == true) {
			this->isCollisionVsBossgenjibo = true;
			genjibo->Update(dt, mPlayer, this->getMapObject());
		}
		else {
			this->isCollisionVsBossgenjibo = false;
		}
		if (genjibo->mExplode[4])
			if (genjibo->mExplode[4]->isEndAnimate)
			{
				genjibo = nullptr;
				isCollisionVsBossgenjibo = false;
			}
	}
		
	if (hornet) {
		if (this->isInCamera(hornet) == true) {
			this->isCollisionVsBossHornet = true;
			hornet->Update(dt, mPlayer, this->getMapObject());
		}
		else {
			this->isCollisionVsBossHornet = false;
		}
		if (hornet->mExplode[4])
			if (hornet->mExplode[4]->isEndAnimate)
			{
				hornet = nullptr;
				isCollisionVsBossHornet = false;
			}
	}
	outtime += dt;
	duration += dt;
	int a = 0;
	for (int i = 0; i < listhelit.size(); i++)
	{
		if (this->isInCamera(listhelit[i]) == false) {
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

	for (size_t i = 0; i < mlistdoor.size(); i++) {
		if (this->isInCamera(mlistdoor[i]) == true) {
			mlistdoor[i]->Update(dt);
		}
	}

	for (int i = 0; i < mlistenemybullets.size(); i++){
		if (this->isInCamera(mlistenemybullets[i]) == true) {
			mlistenemybullets[i]->Update(dt);
		}
	}
		
	if (this->mPlayer->isChangeBullet == true) {
		changeBulletEffect->Update(dt, mPlayer);
	}

	for (int i = 0; i < mlistBox.size(); i++) {
		if (mlistBox.at(i)->isAlive == true) {
			if (this->isInCamera(mlistBox.at(i)) == true) {
				mlistBox.at(i)->Update(dt);
			}
		}
		else {
			mMap->deletenode(mlistBox.at(i));
			std::vector<Box*>::iterator pos = mlistBox.begin();
			mlistBox.erase(pos + i);
			
		}
		
	}
	for (size_t i = 0; i < mlistElevator.size(); i++)
	{
		mlistElevator[i]->Update(dt);
	}

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
	{
		if (this->isInCamera(mlistenemybullets.at(i)) == true) {
			mlistenemybullets.at(i)->Draw(trans);
		}
	}

	if(genjibo && this->isCollisionVsBossgenjibo==true)
		genjibo->Draw(trans);
	if (byte && this->isCollisionVsBossByte==true)
		byte->Draw(trans);
	if (hornet && this->isCollisionVsBossHornet==true)
		hornet->Draw(trans);

	for (int i = 0; i < listhelit.size(); i++)
	{
		if (this->isInCamera(listhelit.at(i)) == true) {
			listhelit.at(i)->Draw(trans);
		}
	}

	for (size_t i = 0; i < mlistdoor.size(); i++)
	{
		if (this->isInCamera(mlistdoor.at(i)) == true) {
			mlistdoor[i]->Draw(trans);
		}
	}

	if (this->mPlayer->isChangeBullet) {
		changeBulletEffect->Draw(trans);
	}

	for (int i = 0; i < mlistBox.size(); i++) {
		if (mlistBox.at(i)->isAlive == true) {
			if (this->isInCamera(mlistBox.at(i)) == true) {
				mlistBox.at(i)->Draw(trans);
			}
		}
		
	}
	for (size_t i = 0; i < mlistElevator.size(); i++)
	{
		mlistElevator[i]->Draw(trans);
	}
}

void DemoScene::EnemyAction()
{
	for (int i = 0; i < mlistGunners.size(); i++)
	{
		if (this->isInCamera(mlistGunners.at(i)) == true) {
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
						ebullet->Spawn(1, mlistGunners.at(i)->GetPosition().x, mlistGunners.at(i)->GetPosition().y - mlistGunners.at(i)->getCurrentAnimation()->GetHeight() / 2, direction*GunnerDefine::BULLET_SPEED_X_1, -GunnerDefine::BULLET_SPEED_Y_1);
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

bool DemoScene::isInCamera(Entity * entityA)
{
	if (entityA->GetBound().left > mCamera->GetBound().right || entityA->GetBound().bottom<mCamera->GetBound().top || entityA->GetBound().top>mCamera->GetBound().bottom || entityA->GetBound().right < mCamera->GetBound().left) {
		return false;
	}
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
				if (bulletlist.at(bulletlist.size() - 1)->posX > mCamera->GetBound().right || bulletlist.at(bulletlist.size() - 1)->posX < mCamera->GetBound().left)
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

		//healthIems
		for (int j = 0; j < mlisItemHealth.size(); j++) {
			if (this->isInCamera(mlisItemHealth.at(j)) == true) {
				Entity::CollisionReturn PlayerVsHealthItems = GameCollision::RecteAndRect(mPlayer->GetBound(), mlisItemHealth.at(j)->GetBound());
				Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, PlayerVsHealthItems);
				Entity::SideCollisions sideHealth = GameCollision::getSideCollision(mlisItemHealth.at(j), PlayerVsHealthItems);
				if (PlayerVsHealthItems.IsCollided) {
					if (mlisItemHealth.at(j)->isAlive == true) {
						mPlayer->OnCollision(mlisItemHealth.at(j), sidePlayer);
						mlisItemHealth.at(j)->OnCollision(mPlayer, sideHealth);
					}
				}
			}
		}

		//escalator
		for (int j = 0; j < mlistEscalator.size(); j++) {
			Entity::CollisionReturn PlayerVsEs = GameCollision::RecteAndRect(mPlayer->GetBound(), mlistEscalator.at(j)->GetBound());
			Entity::SideCollisions side = GameCollision::getSideCollision(mPlayer, PlayerVsEs);
			if (PlayerVsEs.IsCollided) {
				mPlayer->OnCollision(mlistEscalator.at(j), side);
			}
		}
		//doorr
		for (int j = 0; j < mlistdoor.size(); j++) {

			//Door vs Player
			if (this->isInCamera(mlistdoor.at(j)) == true) {
				Entity::CollisionReturn doorVsPlayer = GameCollision::RecteAndRect(mlistdoor.at(j)->GetBound(), this->mPlayer->GetBound());
				Entity::SideCollisions side = GameCollision::getSideCollision(mlistdoor.at(j), doorVsPlayer);
				Entity::SideCollisions sidePlayerVsDoor = GameCollision::getSideCollision(mPlayer, doorVsPlayer);

				
				if (doorVsPlayer.IsCollided) {
					if ((sidePlayerVsDoor == Entity::Right || sidePlayerVsDoor == Entity::Left) && mPlayer->getState() == PlayerState::Jumping)
					{
						mPlayer->SetState(new PlayerClingingState(this->mPlayer->getplayerdata()));
					}
					if (j == 1 && genjibo && (side == Entity::Left || side == Entity::TopLeft || side == Entity::BottomLeft ||side ==Entity::Top) ) {
						mPlayer->AddPositionX(-5);
						continue;
					}
					if (j == 3 && byte && (side == Entity::Left || side == Entity::TopLeft || side == Entity::BottomLeft || side == Entity::Top)) {
						mPlayer->AddPositionX(-5);
						continue;
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
							mPlayer->AddPositionX(5);
						}
					}	
				}
				
		}

			//byte vs door
				if (this->isCollisionVsBossByte) {
					Entity::CollisionReturn byteVsDoor = GameCollision::RecteAndRect(mlistdoor.at(j)->GetBound(), this->byte->GetBound());
					Entity::SideCollisions sideByte = GameCollision::getSideCollision(this->byte,byteVsDoor);
					if (byteVsDoor.IsCollided) {
						this->byte->OnCollision(mlistdoor.at(j), sideByte);
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

			//bomp vs door 
			if (this->isCollisionVsBossByte) {
				if (byte->bomp) {
					Entity::CollisionReturn bompByteVsDoor = GameCollision::RecteAndRect(mlistdoor.at(j)->GetBound(), this->byte->bomp->GetBound());
					Entity::SideCollisions sideBompByte = GameCollision::getSideCollision(this->byte->bomp, bompByteVsDoor);
					if (bompByteVsDoor.IsCollided) {
						this->byte->bomp->OnCollision(mlistdoor.at(j), sideBompByte);
					}
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
			if (this->isInCamera(mlistGunners.at(j)) == true) {
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
		
			//box
			for (int h = 0; h < mlistBox.size(); h++) {
				if (mlistBox.at(h)->isAlive == true) {
					if (this->isInCamera(mlistBox.at(h)) == true) {
						Entity::CollisionReturn PlayerBulletVsBox = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), mlistBox.at(h)->GetBound());
						Entity::SideCollisions sideBox = GameCollision::getSideCollision(mlistBox.at(h), PlayerBulletVsBox);
						if (PlayerBulletVsBox.IsCollided) {
							mlistBox.at(h)->OnCollision(bulletlist.at(j), sideBox);
							bulletlist.at(j)->OnCollision();

						}

					}
				}
			}

			if (mMap->isCollisionVsGunner) {
 				for (int h = 0; h < mlistGunners.size(); h++) {
					if (this->isInCamera(mlistGunners.at(h)) == true) {
						Entity::CollisionReturn PlayerBulletVsBot = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), mlistGunners.at(h)->GetBound());
						if (PlayerBulletVsBot.IsCollided) {
							mlistGunners.at(h)->setHealthPoint(bulletlist.at(j)->Tag);
							bulletlist.at(j)->OnCollision();
							if (mlistGunners.at(h)->getHealthPoint() <= 0) {
								Sound::getInstance()->play("explosion", false, 1);
								mlistGunners.at(h)->changeAnimation(EnemyState::Die);
								mlistGunners.at(h)->isAlive = false;
								std::vector<Enemy*>::iterator pos = mlistGunners.begin();
								mlistGunners.erase(pos + h);
							}
						}
					}
				}
			}
			
			if (this->isCollisionVsHelit) {
				for (int h = 0; h < listhelit.size(); h++) {
					if (this->isInCamera(listhelit.at(h)) == true) {
						Entity::CollisionReturn PlayerBulletVsHelit = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), listhelit.at(h)->GetBound());
						if (PlayerBulletVsHelit.IsCollided) {
							bulletlist.at(j)->OnCollision();
							if (listhelit.at(h)->isAlive == false) {
								Sound::getInstance()->play("explosion", false, 1);
								std::vector<Helit*>::iterator pos = listhelit.begin();
								listhelit.erase(pos + h);
							}
						}
					}
				}
			}
			
			if (this->isCollisionVsBossgenjibo) {
				if (genjibo)
				{
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
			//honert 
			if (this->isCollisionVsBossHornet) {
				if (hornet)
				{
					Entity::CollisionReturn ex = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
						hornet->GetBound());
					if (ex.IsCollided)
					{
						Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(hornet, ex);
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

		//boss byte
		if (byte) {
			if (this->isCollisionVsBossByte) {
				//byte vs player
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

				//bomp byte
				if (byte->bomp) {
					//bomp Byte Vs Static
					Entity::CollisionReturn bompByteVsStatic = GameCollision::RecteAndRect(this->byte->bomp->GetBound(), listCollision.at(i)->GetBound());
					Entity::SideCollisions sideBompByteVsStatic = GameCollision::getSideCollision(byte->bomp, bompByteVsStatic);
					if (bompByteVsStatic.IsCollided) {
						byte->bomp->OnCollision(listCollision.at(i), sideBompByteVsStatic);
					}

					//bomp Byte vs Byte 
					Entity::CollisionReturn bomByteVsByte = GameCollision::RecteAndRect(this->byte->bomp->GetBound(), this->byte->GetBound());
					Entity::SideCollisions sideBompByteVsByte = GameCollision::getSideCollision(byte->bomp, bomByteVsByte);
					Entity::SideCollisions sideByte = GameCollision::getSideCollision(byte, bomByteVsByte);

					if (bomByteVsByte.IsCollided) {
						byte->bomp->OnCollision(this->byte, sideBompByteVsByte);
						byte->OnCollision(this->byte->bomp, sideByte);
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
		if (this->isInCamera(listCollision.at(i)) == true) {
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
					|| sidePlayer == Entity::BottomRight)
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
				if (sidePlayer == Entity::Top || sidePlayer == Entity::TopLeft || sidePlayer == Entity::TopRight) {
					mPlayer->AddPositionY(5);
					mPlayer->SetState(new PlayerFallingState(this->mPlayer->getplayerdata()));
				}
			}
		}
	}

	if (mMap->isStopCamera == true && mPlayer->GetBound().left <= mCamera->GetBound().left) {
		this->mPlayer->AddPositionX(10);
	}

	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}