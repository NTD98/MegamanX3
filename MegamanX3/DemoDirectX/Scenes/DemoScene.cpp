#include "DemoScene.h"
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
	mPlayer->SetPosition(5000.00, 1923.00);
    mPlayer->SetCamera(mCamera);
	generate();
}

void DemoScene::Update(float dt)
{
	if (byte)
		byte->Update(dt, mPlayer, this->getMapObject());
	if(genjibo)
	genjibo->Update(dt, mPlayer, this->getMapObject());
	duration += dt;
	for (int i = 0; i < listhelit.size(); i++)
	{
		listhelit.at(i)->Update(dt, mPlayer, this->getMapObject());
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
	mMap->Draw(mPlayer->GetPosition().x / 32, mPlayer->GetPosition().y / 32);
	
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
	if(genjibo)
		genjibo->Draw(trans);
	if (byte)
		byte->Draw(trans);
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
	if (bulletlist.size()==0)
	{
		
	}
	else
	{
		for (auto it = bulletlist.begin(); it != bulletlist.end();)
		{
			if (bulletlist.at(bulletlist.size() - 1)->GetBound().left > mCamera->GetBound().right|| bulletlist.at(bulletlist.size() - 1)->GetBound().right < mCamera->GetBound().left)
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

void DemoScene::checkCollision()
{
	int widthBottom = 0;
	D3DXVECTOR2 pos(this->mPlayer->GetPosition().x, this->mPlayer->GetPosition().y);
	vector<Entity*> listCollision;
	vector<Bullet*> bulletlist = mPlayer->getbulletlist();
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
	mapobject = listCollision;
	//player and player's bullet
	for (size_t i = 0; i < listCollision.size(); i++)
	{
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
		for (int j = 0; j < mlistGunners.size(); j++)
		{
			int widthBottomE = 0;
			Entity::CollisionReturn botVsPlayer = GameCollision::RecteAndRect(mlistGunners.at(j)->GetBound(),mPlayer->GetBound());
			Entity::CollisionReturn g = GameCollision::RecteAndRect(mlistGunners.at(j)->GetBound(),listCollision.at(i)->GetBound());
		
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
			if (botVsPlayer.IsCollided)
			{
				//lay phia va cham cua Entity so voi Player
				Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, botVsPlayer);
				//lay phia va cham cua Player so voi Entity
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mlistGunners.at(j), botVsPlayer);
				if (this->mPlayer->isAlive == true && this->mPlayer->isBeforeDeath==false) {
					if (this->mPlayer->isTimeNoDame == false) {
						this->mPlayer->SetState(new PlayerDameState(this->mPlayer->getplayerdata()));
						if (this->mPlayer->isSetHealth == true ||this->mPlayer->getHealthPoint()==16) {
						this->mPlayer->setHealthPoint(mlistGunners.at(j)->Tag, true);
						this->mPlayer->isSetHealth = false;
						}
					}
					if (this->mPlayer->getHealthPoint() <= 0) {
						this->mPlayer->SetState(new PlayerDeathState(this->mPlayer->getplayerdata(),pos.x,pos.y));
						this->mPlayer->isBeforeDeath = true;
					}
				}
			}
			

		}
		//enemy bullet
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
		for (size_t j = 0; j < bulletlist.size(); j++)
		{
			//Entity::CollisionReturn b = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),listCollision.at(i)->GetBound());
			//if (b.IsCollided)
			//{
			//	//bulletlist.at(j)->OnCollision();
			//}


			for (int h = 0; h < mlistGunners.size(); h++) {
				Entity::CollisionReturn PlayerBulletVsBot = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(), mlistGunners.at(h)->GetBound());
				if (PlayerBulletVsBot.IsCollided) {
					mlistGunners.at(h)->setHealthPoint(bulletlist.at(j)->Tag);
					bulletlist.at(j)->OnCollision();
					if (mlistGunners.at(h)->getHealthPoint() <=0 ) {
						mlistGunners.at(h)->changeAnimation(EnemyState::Die);
						mlistGunners.at(h)->isAlive = false;
						std::vector<Enemy*>::iterator pos = mlistGunners.begin();
						for (int m = 1; m < h; m++)
							pos++;
						mlistGunners.erase(pos);
					}
				}
			}
			for (int h = 0; h < listhelit.size(); h++) {
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
			if (genjibo)
			{
				Entity::CollisionReturn ex = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
					genjibo->GetBound());
				if (ex.IsCollided)
				{
					Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(genjibo, ex);

					//lay phia va cham cua Player so voi Entity
					genjibo->OnCollision(bulletlist.at(j), sidePlayer);
					bulletlist.at(j)->OnCollision();
				}
			}
			if (byte)
			{
				Entity::CollisionReturn ex = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
					byte->GetBound());
				if (ex.IsCollided)
				{
					Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(byte, ex);

					//lay phia va cham cua Player so voi Entity
					byte->OnCollision(bulletlist.at(j), sidePlayer);
					bulletlist.at(j)->OnCollision();
				}
			}
		}
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

			//kiem tra neu va cham voi phia duoi cua Player 
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
		}
	}
	

	//Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}