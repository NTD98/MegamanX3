#include "GameMap.h"
#include <windows.h>
#include <d3d9.h>
#include"GameGlobal.h"
#include <fstream>
#include <iostream>
std::ofstream out("Entity.txt");
GameMap::GameMap()
{
	
}

GameMap::GameMap(char* filePath)
{
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    LoadMap(filePath);
	/*this->map = new Sprite("Resources/megaman/pic10.png");
	this->map->SetPosition(100, 2306.8);
	this->map->Draw();*/
}



GameMap::~GameMap()
{
	delete mMap;

	for (size_t i = 0; i < mListGunners.size(); i++)
	{
		if (mListGunners[i])
			delete mListGunners[i];
	}
	mListGunners.clear();

	for (size_t i = 0; i < mlistElevator.size(); i++)
	{
		if (mlistElevator[i])
			delete mlistElevator[i];
	}
	mlistElevator.clear();

    for (size_t i = 0; i < mListTileset.size(); i++)
    {
        if (mListTileset[i])
            delete mListTileset[i];
    }
    mListTileset.clear();

    delete mQuadTree;
}
void GameMap::LoadMap(char* filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);
    RECT r;
    r.left = 0;
    r.top = 0;
	r.right = 1000;
	r.bottom = 1000;

    mQuadTree = new QuadTree(1, r);



    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = mMap->GetTileset(i);

        Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str());
        mListTileset.insert(pair<int, Sprite*>(i, sprite));
    }

    //khoi tao cac khoi Brick (vien gach)

	for (size_t i = 0; i < GetMap()->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (layer->IsVisible())
			continue;

		//xac dinh layer Brick bi an di de tu do tao ra cac vien gach trong game, nhung vien gach khong phai la 1 physic static nos co the bi pha huy duoc

			for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
			{
				const Tmx::Tileset *tileSet = mMap->GetTileset(j);

				int tileWidth = mMap->GetTileWidth();
				int tileHeight = mMap->GetTileHeight();

				int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
				int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

				for (size_t m = 0; m < layer->GetHeight(); m++)
				{
					for (size_t n = 0; n < layer->GetWidth(); n++)
					{
						if (layer->GetTileTilesetIndex(n, m) != -1)
						{
							int tileID = layer->GetTileId(n, m);

							int y = tileID / tileSetWidth;
							int x = tileID - y * tileSetWidth;

							RECT sourceRECT;
							sourceRECT.top = y * tileHeight;
							sourceRECT.bottom = sourceRECT.top + tileHeight;
							sourceRECT.left = x * tileWidth;
							sourceRECT.right = sourceRECT.left + tileWidth;

							RECT bound;
							bound.left = n * tileWidth;
							bound.top = m * tileHeight;
							bound.right = bound.left + tileWidth;
							bound.bottom = bound.top + tileHeight;

							D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

							//gunner
							if (layer->GetName() == "gunner")
							{
								Gunner *gunner = new Gunner(position);
							    gunner->Tag = Entity::EntityTypes::Gunner;
								mListGunners.push_back(gunner);
								//mQuadTree->insertEntity(gunner);
							}
							else
							//elevator
								if (layer->GetName() == "elevator") {
									Elevator *elevator = new Elevator(position);
									mlistElevator.push_back(elevator);
									mQuadTree->insertEntity(elevator);
								}
							else
								if (layer->GetName() == "headgunner")
								{
									HeadGunner *headgunner = new HeadGunner(position);
									headgunner->Tag = Entity::EntityTypes::HeadGunner;
									mListGunners.push_back(headgunner);
								}
								else {
									if (layer->GetName() == "box2") {
										Box *box2 = new Box(position.x,position.y+5,2);
										mListBox.push_back(box2);
										mQuadTree->insertEntity(box2);
									}
								}
						}
					}
				}
		}
	}
#pragma region -OBJECTGROUP, STATIC OBJECT-

    for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
    {
        const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

        for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
        {
            //lay object group chu khong phai layer
            //object group se chua nhung body
            Tmx::Object *object = objectGroup->GetObjects().at(j);

            Entity *entity = new Entity();
            entity->SetPosition(object->GetX() + object->GetWidth()/2,object->GetY() + object->GetHeight()/2);
            entity->SetWidth(object->GetWidth());
            entity->SetHeight(object->GetHeight());
            entity->Tag = Entity::EntityTypes::Static;

            mQuadTree->insertEntity(entity);
			switch (entity->Tag)
			{
			case 4: out << "Static " << "x: " << std::to_string(entity->GetPosition().x)<<" "<<"y: "<< std::to_string(entity->GetPosition().y)<<" "<<"width "<< std::to_string(entity->GetWidth())<<" height "<< std::to_string(entity->GetHeight())<<"\n";
			default:
			break;
			}
        }
    }
	out.close();
#pragma endregion
}

void GameMap::SetCamera(Camera* camera)
{
    mCamera = camera;
}



Tmx::Map* GameMap::GetMap()
{
    return mMap;
}

RECT GameMap::GetWorldMapBound()
{
    RECT bound;
    bound.left = bound.top = 0;
    bound.right = mMap->GetWidth() * mMap->GetTileWidth();
    bound.bottom = mMap->GetHeight() * mMap->GetTileHeight();

    return bound;
}

int GameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

bool GameMap::IsBoundLeft()
{
    return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
    return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
    return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
    return (mCamera->GetBound().bottom == this->GetHeight());
}


void GameMap::Update(float dt)
{
	int a = 0;
	for (int i = 0; i < mListGunners.size(); i++)
	{
		if (mListGunners[i]->GetBound().left > mCamera->GetBound().right || mListGunners[i]->GetBound().bottom<mCamera->GetBound().top || mListGunners[i]->GetBound().top>mCamera->GetBound().bottom || mListGunners[i]->GetBound().right < mCamera->GetBound().left) {
			a++;
			continue;
		}
		if (mListGunners[i]->isAlive) {
				mListGunners[i]->Update(dt);
		}
		this->isCollisionVsGunner = true;
	}
	
	if (a == mListGunners.size()) {
		this->isCollisionVsGunner = false;
	}
	
	for (size_t i = 0; i < mlistElevator.size(); i++)
	{
		mlistElevator[i]->Update(dt);
	}
	
}

void GameMap::Draw(int beginX, int beginY)
{
	int maxX = 0, maxY = 0;
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
	if (beginX < 10)
		beginX = 0;
	else
		beginX -= 10;
	if (beginY < 10)
		beginY = 0;
	else
		beginY -= 10;

#pragma region DRAW TILESET
    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
        {
            const Tmx::Tileset *tileSet = mMap->GetTileset(j);

            RECT sourceRECT;

            int tileWidth = mMap->GetTileWidth();
            int tileHeight = mMap->GetTileHeight();

            int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
            int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;
			if (beginX + 22 > layer->GetWidth())
				maxX = layer->GetWidth();
			else
				maxX = beginX + 22;
			if (beginY + 22 > layer->GetHeight())
				maxY = layer->GetHeight();
			else
				maxY = beginY + 22;
			for (size_t m = beginY; m < maxY; m++)
			{
				for (size_t n = beginX; n < maxX; n++)
				{
                    if (layer->GetTileTilesetIndex(n, m) != -1)
                    {
                        int tileID = layer->GetTileId(n, m);

                        int y = tileID / tileSetWidth;
                        int x = tileID - y * tileSetWidth;

                        sourceRECT.top = y * tileHeight;
                        sourceRECT.bottom = sourceRECT.top + tileHeight;
                        sourceRECT.left = x * tileWidth;
                        sourceRECT.right = sourceRECT.left + tileWidth;

                        Sprite* sprite = mListTileset[j];

                        //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                        //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                        D3DXVECTOR3 position(n * tileWidth + tileWidth/2, m * tileHeight + tileHeight/2, 0);

                        if (mCamera != NULL)
                        {
                            RECT objRECT;
							objRECT.left = position.x - tileWidth / 2;
                            objRECT.top = position.y - tileHeight/2;
                            objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

                            if (!GameCollision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
                                continue;
                        }

                        sprite->SetWidth(tileWidth);
                        sprite->SetHeight(tileHeight);

                        sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                    }
                }
            }
        }
    }
#pragma endregion
#pragma region DRAW MAP OBJECT
	for (size_t i = 0; i < mlistElevator.size(); i++)
	{
		mlistElevator[i]->Draw(trans);
	}
	for (size_t i = 0; i < mListGunners.size(); i++)
	{
		if (mListGunners[i]->GetBound().left > mCamera->GetBound().right || mListGunners[i]->GetBound().bottom<mCamera->GetBound().top || mListGunners[i]->GetBound().top>mCamera->GetBound().bottom || mListGunners[i]->GetBound().right < mCamera->GetBound().left) {
			continue;
		}
		if(mListGunners[i]->isAlive)
		mListGunners[i]->Draw(trans);
	}
	
#pragma endregion
	
}

std::map<int, Sprite*> GameMap::getListTileSet()
{
    return mListTileset;
}

QuadTree * GameMap::GetQuadTree()
{
    return mQuadTree;
}

vector<Enemy*> GameMap::getEnemy()
{
	return mListGunners;
}

vector<Box*> GameMap::getBox()
{
	return mListBox;
}
