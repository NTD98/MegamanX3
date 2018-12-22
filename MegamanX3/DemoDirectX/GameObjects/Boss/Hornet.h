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
	Hornet(float posX, float posY,Player* mPlayer,Camera* mCamera);
	void Update(float dt, Player* mPlayer, vector<Entity*> mListMapObject);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	Animation* mExplode[5];
	void Draw(D3DXVECTOR2 transform);
protected:
	void SpawnChild1();
	void SpawnFollow();
	Animation *mAnimation, *mAnimationAttack, *mAnimationSpawnChild, *mAnimationDie,
		*mAnimationFly,*mAnimationStand, *mAnimationPrepare, *mAnimationFollow;
	Player* mPlayer;
	Camera* mCamera;
	ChildHornet *mChild;
	ChildHornet *mChildFollow;
	std::vector<ChildHornet* > mListChild;
	RECT rectMove;
	int midRectY;
	int typeAttack, iExplosion;
	int direction;
	float posX1, posY1;
	int posMegaX, posMegaY;
	bool toAttack,isAttack;
	bool onDraw;
};
