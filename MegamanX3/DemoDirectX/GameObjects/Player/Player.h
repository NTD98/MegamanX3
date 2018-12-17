#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "bullet.h"
#include "../Effect/PlayerFlashDashEffect.h"
#include "../Effect//PlayerSmokeDashEffect.h"

class Player : public Entity
{
public:
    Player();
    ~Player();

    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
		jumping,
        None //dung im
    };


    void SetCamera(Camera *camera);

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(PlayerState *newState);
	/*void SetState(PlayerState *newState,bool ActionAndShoot);*/

    void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

    void OnNoCollisionWithBottom();

    MoveDirection getMoveDirection();

    RECT GetBound();     

    PlayerState::StateName Player::getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys);

    void OnKeyPressed(int key);

    void OnKeyUp(int key);
	void changeAnimation(PlayerState::StateName state);
	void noDameChangeAnimation(PlayerState::StateName state);
	Animation* getCurrentAnimation();
    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);
	bool GetReverse();
	bool isDead = false;
	bool isDone = false;
	bool isTimeNoDame = false;
	bool isSetHealth = false;
    bool allowMoveLeft;
	int getHealthPoint();
	void setHealthPoint();
	void spawning();
    bool allowMoveRight;
	vector<Bullet*> getbulletlist(); 
	void deletebullet();
	PlayerData* getplayerdata();
	PlayerFlashDashEffect *mlistFlashEffect;
	PlayerSmokeDashEffect *mlistSmokeEffect;
	PlayerState::StateName mCurrentState;
	float dtBeDame = 0, dtTimeNoDame = 0;
protected:
    Camera      *mCamera;

    PlayerData *mPlayerData;

	Animation   *mCurrentAnimation,
		*mAnimationStanding,
		*mAnimationRunning,
		*mAnimationJumping,
		*mAnimationSpawning,
		*mAnimationClinging,
		*mAnimationClingingJ,
		*mAnimationDashing,
		*mAnimationStandShoot,
		*mAnimationJumpShoot,
		*mAnimationRunnShoot,
		*mAnimationDashShoot,
		*mAniamtionClingShoot,
		*mAnimationClingJShoot,
		*mAnimationDead,
		*mAniamtionBeDame,

		// No being dame
		*mAnimationNoDameStand,
		*mAnimationNoDameRun,
		*mAnimationNoDameJumping,
		*mAnimationNoDameClinging,
		*mAnimationNoDameClingingJ,
		*mAnimationNoDameDashing,
		*mAnimationNoDameStandShoot,
		*mAnimationNoDameJumpShoot,
		*mAnimationNoDameRunnShoot,
		*mAnimationNoDameDashShoot,
		*mAniamtionNoDameClingShoot,
		*mAnimationNoDameClingJShoot;

	vector <Bullet*> bulletlist;
	
   
	
	int HealthPoint = 16;
    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool allowJump, mCurrentReverse, allowshoot = true;
	

	void InitAni();
	
};

