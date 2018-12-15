#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Player/PlayerDeadState.h"

class DemoScene : public Scene
{
public:
    DemoScene();
    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
	bool iscolidebullet(RECT a, RECT b);
	void isDead();
protected:
    void checkCollision();
    void CheckCameraAndWorldMap();

    GameMap *mMap;
    Camera *mCamera;
    Player *mPlayer;
	Sprite *map;
	Sprite *HealthBar,
		*HealthPoint;
	vector<Sprite*> Health;
    std::map<int, bool> keys;
};

