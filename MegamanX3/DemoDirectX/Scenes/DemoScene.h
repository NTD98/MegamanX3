#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Player/PlayerDameState.h"
#include "../GameObjects/Player/PlayerClingingState.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemy/EnemyBullet.h"
#include "../GameObjects/Boss/Genjibo.h"
#include "../GameObjects/Enemy/Helit.h"
#include "../GameObjects/Player/PlayerStandingState.h"
#include "../GameObjects/Boss/Byte.h"
#include "../GameObjects/Player/PlayerFallingState.h"
#include "../GameObjects/MapObjects/Door.h"
#include "../GameObjects/Boss/Hornet.h"
#include "../GameObjects/Boss/bomp.h"
#include "../GameObjects/Effect/ChangeBulletEffect.h"
#include "../GameObjects/MapObjects/Elevator.h"
class DemoScene : public Scene
{
public:
    DemoScene();
	void generate();
    void Update(float dt);
    void LoadContent();
    void Draw();
	void EnemyAction();
    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
	bool iscolidebullet(RECT a, RECT b);
	bool isInCamera(Entity *entityA );
	vector<Entity*> getMapObject();
protected:
	vector<Entity*> mapobject;
    void checkCollision();
    void CheckCameraAndWorldMap();
	float duration = 0.0f;
    GameMap *mMap;
    Camera *mCamera;
    Player *mPlayer;
	Sprite *map;
	Sprite *HealthBar,
		*HealthPoint;
	Genjibo* genjibo;
	Byte* byte;
	Hornet* hornet;
	vector<Enemy*> mlistGunners;
	vector<EnemyBullet*> mlistenemybullets;
	vector<Sprite*> Health;
	vector<Helit*> listhelit;
	vector<Door*> mlistdoor;
	vector<Box*> mlistBox;
	vector<Elevator*> mlistElevator;
    std::map<int, bool> keys;
	bool isCollisionVsHelit;
	bool isCollisionVsBossByte;
	bool isCollisionVsBossgenjibo;
	bool isCollisionVsBossHornet;
	ChangeBulletEffect *changeBulletEffect;
};

