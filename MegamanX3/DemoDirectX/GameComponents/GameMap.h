#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/Enemy/Gunner.h"
#include "../GameObjects/MapObjects/Elevator.h"
#include "../GameObjects/Enemy/HeadGunner.h"
#include "../GameObjects/MapObjects/Door.h"
#include "../GameObjects/Boss/Genjibo.h"
#include "../GameObjects/Boss/Byte.h"
#include "../GameObjects/Boss/Hornet.h"
#include "../GameObjects/MapObjects/Box.h"
#include "../GameObjects/MapObjects/Escalator.h"
#include "../GameObjects/MapObjects/ItemsHealth.h"
class GameMap
{
public:
	GameMap();
    GameMap(char* filePath);
    void SetCamera(Camera* camera);
    void Update(float dt);
	void Draw(int beginX, int beginY);
    Tmx::Map* GetMap();
    RECT GetWorldMapBound();
	
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
    std::map<int, Sprite*> getListTileSet();
	vector<Enemy*> getEnemy();
	vector<Box*> getBox();
    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();
    QuadTree* GetQuadTree();
	bool isCollisionVsGunner;
	bool isStopCamera;
	bool isDaChuyenCanh = false;
	QuadTree                        *mQuadTree;
	void DeleteEntity(Entity* entity);
	vector<Escalator*> mlistEscalator;
	vector<ItemsHealth*> mlistHealth;
	vector<Elevator*> mlistElevator;
	void deletenode(Entity* entity);
private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
   
	std::vector<Enemy*>			mListGunners;
	std::vector<Box*> mListBox;
	Sprite *map;


	
};

#endif

