#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "../Enemy/ChildHornet.h"
#include "HornetHP.h"

class Hornet : public Entity
{
public:
	~Hornet();
	Hornet(float posX, float posY, Player* mPlayer, Camera* mCamera);
	void Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject);
	void OnCollision(Entity * other, SideCollisions side);
	Animation* mExplode[5];
	void Draw(D3DXVECTOR2 transform);
	int count = 0;
	ChildHornet *mChild;
	ChildHornet *mChildFollow;
	std::vector<ChildHornet* > mListChild;
protected:
	void SpawnChild1();
	void SpawnFollow();
	Animation *mAnimation, *mAnimationAttack, *mAnimationSpawnChild, *mAnimationDie,
		*mAnimationFly, *mAnimationStand, *mAnimationPrepare, *mAnimationFollow;
	Player* mPlayer;
	Camera* mCamera;
	RECT rectMove;
	int midRectY;
	int typeAttack, iExplosion;
	int direction;
	float posX1, posY1;
	int posMegaX, posMegaY;
	bool toAttack, isAttack;
	bool onDraw;
};
