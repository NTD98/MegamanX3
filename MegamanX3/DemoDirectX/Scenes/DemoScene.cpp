#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x54acd2;

    mMap = new GameMap("Resources/mario.tmx");

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
    mPlayer = new Player();
	//50/1340
    mPlayer->SetPosition(50, 900);

    mPlayer->SetCamera(mCamera);
}

void DemoScene::Update(float dt)
{
	if (mPlayer->getState() != PlayerState::Spawning)
		checkCollision();

    mMap->Update(dt);

    mPlayer->HandleKeyboard(keys);

    mPlayer->Update(dt);

    CheckCameraAndWorldMap();

	HealthBar->SetPosition(D3DXVECTOR2(mCamera->GetPosition().x - 260, mCamera->GetPosition().y - 200));
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
			pos = D3DXVECTOR3(HealthBar->GetPosition().x, HealthBar->GetPosition().y + 18, 0);
		Health.at(i)->Draw(pos, RECT(), D3DXVECTOR2(1, 1), trans);
		pos = pos + D3DXVECTOR3(0, -4, 0);
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

    vector<Entity*> listCollision;
	vector<Bullet*> bulletlist = mPlayer->getbulletlist();
    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
	
    for (size_t i = 0; i < listCollision.size(); i++)
    {
		for (size_t j = 0; j < bulletlist.size(); j++)
		{
			Entity::CollisionReturn b = GameCollision::RecteAndRect(bulletlist.at(j)->GetBound(),
				listCollision.at(i)->GetBound());
			if (b.IsCollided)
			{
				bulletlist.at(j)->OnCollision();
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
			if ((sidePlayer == Entity::Right || sidePlayer == Entity::Left)&&mPlayer->getState()==PlayerState::Jumping)
			{
				mPlayer->changeAnimation(PlayerState::Clinging);
			}
        }
    }

    //Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
    if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
    {
        mPlayer->OnNoCollisionWithBottom();
    }
}