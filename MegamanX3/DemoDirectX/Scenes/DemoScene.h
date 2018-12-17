#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Player/PlayerDameState.h"
#include "../GameObjects/Effect/PlayerDeathEffect.h"
//#include "../GameObjects/Player/PlayerClingingState.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemy/EnemyBullet.h"
#include "../GameObjects/Boss/Genjibo.h"
class DemoScene : public Scene
{
public:
    DemoScene();
    void Update(float dt);
    void LoadContent();
    void Draw();
	void EnemyAction();
    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
	bool iscolidebullet(RECT a, RECT b);
	void isDead();
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
	vector<Enemy*> mlistGunners;
	vector<EnemyBullet*> mlistenemybullets;
	vector<Sprite*> Health;
	PlayerDeathEffect *mAnimationDeathEffect;
    std::map<int, bool> keys;
};

