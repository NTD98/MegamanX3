#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSpawingState.h"
#include "PlayerStandingState.h"
#include "PlayerClingingState.h"
#include "PlayerClingingJState.h"
#include "PlayerDashState.h"
#include "PlayerDameState.h"
#include "../../GameComponents/GameCollision.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/Sound.h"
float check = 0.0;
bool isDone = false;
Player::Player()
{
	InitAni();
	Sound::getInstance()->loadSound("Resources/Sound/Jump.wav", "Jump");
	Sound::getInstance()->loadSound("Resources/Sound/Dass.wav", "Dass");
	Sound::getInstance()->loadSound("Resources/Sound/Die.wav", "Die");
	Sound::getInstance()->loadSound("Resources/Sound/PlayerShoot.wav", "shoot");
    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerSpawingState(this->mPlayerData));
	this->Tag = Entity::EntityTypes::Megaman;
    allowJump = true;
	mlistFlashEffect = new PlayerFlashDashEffect[5];
	mlistSmokeEffect = new PlayerSmokeDashEffect[9];
	this->isAlive = true;
	isFollow = false;
}

Player::~Player()
{
}

void Player::InitAni()
{
	//Trạng thái bình thường của nhân vật
	mAnimationStanding = new Animation("Resources/megaman/standing.png", 3, 1, 3, 0.2f);
	mAnimationJumping = new Animation("Resources/megaman/pic3.png", 7, 1, 7, 0.1f);
	mAnimationRunning = new Animation("Resources/megaman/pic2.png", 11, 1, 11, 0.05f);
	mAnimationSpawning = new Animation("Resources/megaman/pic7.png", 7, 1, 7, 0.1f);
	mAnimationStandShoot = new Animation("Resources/megaman/standShoot.png", 2, 1, 2, 0.5f);
	mAnimationJumpShoot = new Animation("Resources/megaman/JumpShoot.png", 6, 1, 6, 0.1f);
	mAnimationRunnShoot = new Animation("Resources/megaman/RunnShoot.png", 10, 1, 10, 0.05f);
	mAnimationDashShoot = new Animation("Resources/megaman/dashshoot.png", 2, 1, 2, 0.1f);
	mAniamtionClingShoot = new Animation("Resources/megaman/ClingShoot.png", 3, 1, 3, 0.1f);
	mAnimationClingJShoot = new Animation("Resources/megaman/ClingJShoot.png", 2, 1, 2, 0.1f);
	mAnimationDashing = new Animation("Resources/megaman/dash.png", 2, 1, 2, 0.2f, D3DCOLOR_XRGB(0, 0, 0));
	mAnimationClinging = new Animation("Resources/megaman/Cling.png", 3, 1, 3, 0.15f);
	mAnimationClingingJ = new Animation("Resources/megaman/ClingJ.png", 2, 1, 2, 0.15f);
	mAniamtionBeDame = new Animation("Resources/megaman/beDame.png", 10, 1, 10, 0.1f);
	mAnimationBeforeDeath = new Animation("Resources/megaman/BeforeDeath.png", 2, 1, 2, 0.1f);

	//Trạng thái vô hiệu dame của nhân vật
	mAnimationNoDameStand = new Animation("Resources/megaman/noDameStand.png", 2, 1, 2, 0.03f);
	mAnimationNoDameRun = new Animation("Resources/megaman/noDameRun.png", 22, 1, 22, 0.03f);
	mAnimationNoDameJumping = new Animation("Resources/megaman/noDameJump.png", 14, 1, 14, 0.1f);
	mAnimationNoDameStandShoot = new Animation("Resources/megaman/noDameStandShoot.png", 4, 1, 4, 0.5f);
	mAnimationNoDameJumpShoot = new Animation("Resources/megaman/noDameJumpShoot.png", 12, 1, 12, 0.1f);
	mAnimationNoDameRunnShoot = new Animation("Resources/megaman/noDameRunShoot.png", 20, 1, 20, 0.05f);
	mAnimationNoDameDashShoot = new Animation("Resources/megaman/noDameDashShoot.png", 4, 1, 4, 0.1f);
	mAniamtionNoDameClingShoot = new Animation("Resources/megaman/noDameClingShoot.png", 6, 1, 6, 0.1f);
	mAnimationNoDameClingJShoot = new Animation("Resources/megaman/noDameClingJShoot.png", 4, 1, 4, 0.1f);
	mAnimationNoDameDashing = new Animation("Resources/megaman/noDameDash.png", 4, 1, 4, 0.2f, D3DCOLOR_XRGB(0, 0, 0));
	mAnimationNoDameClinging = new Animation("Resources/megaman/noDameCling.png", 6, 1, 6, 0.15f);
	mAnimationNoDameClingingJ = new Animation("Resources/megaman/noDameClingJ.png", 4, 1, 4, 0.15f);
}

void Player::Update(float dt)
{
	if (this->isDungYen == false) {

		for (int i = 0; i < bulletlist.size(); i++)
		{
			if (bulletlist.at(i)->isdelete)
			{
				std::vector<Bullet*>::iterator pos = bulletlist.begin();
				for (int m = 1; m < i; m++)
					pos++;
				bulletlist.erase(pos);
			}
		}
		if (mCurrentState == PlayerState::BeDame) { //Nếu đang bị trạng thái ăn dame thì tăng biến thời gian bị dame
			this->dtBeDame += dt;
		}

		if (mCurrentState == PlayerState::BeDame && dtBeDame >= 0.3f) { // Sau 1s load state ăn dame thì chuyển về Stand 
			this->SetState(new PlayerStandingState(this->mPlayerData));
			dtBeDame = 0;
		}
		if (isTimeNoDame == true) {//Nếu trong thời gian không ăn dame thì tăng biến thời gian không ăn dame
			dtTimeNoDame += dt;
		}
		else {
			dtTimeNoDame = 0;
		}
		if (this->isTimeNoDame == true) {
			if (dtTimeNoDame > 2.0f) {
				this->mPlayerData->player->changeAnimation(mCurrentState);
				this->isTimeNoDame = false;
			}
			else {
				if (dtTimeNoDame != 0) {//Trong khoảng thời gian vô hiệu hóa nhận dame thì chuyển aniamtion nhấp nháy 
					this->mPlayerData->player->noDameChangeAnimation(mCurrentState);
				}
			}
		}

		if (isGetOutGunAnimation == true) {
			dtChangBullet += dt;
		}
		else {
			dtChangBullet = 0;
		}

		if (dtChangBullet >= 0.2f) {
			this->isChangeBullet = true;
		}
		else {
			this->isChangeBullet = false;
		}



		for (int i = 0; i < sizeof(mlistSmokeEffect); i++) {
			mlistSmokeEffect[i].Update(dt, mPlayerData->player->GetPosition(), mPlayerData->player->GetReverse(), mPlayerData->player->GetWidth(), mPlayerData->player->GetHeight());
		}

		for (int i = 0; i < sizeof(mlistFlashEffect); i++) {
			mlistFlashEffect[i].Update(dt, mPlayerData->player->GetPosition(), mPlayerData->player->GetReverse(), mPlayerData->player->GetWidth(), mPlayerData->player->GetHeight());
		}

		bulletlist = this->getbulletlist();
		if (dt >= 1 / 60)
		{
			check += dt;
		}
		switch (mPlayerData->state->GetState())
		{
		case PlayerState::Clinging: case PlayerState::ClingingJ: case PlayerState::Dash:
			mCurrentAnimation->UpdateS(dt);
			break;
		default:
			mCurrentAnimation->Update(dt);
			break;
		}

		if (check >= 0.15 * 7 && isDone == false)
		{
			this->SetState(new PlayerStandingState(this->mPlayerData));
			isDone = true;
		}
		if (this->mPlayerData->state)
		{
			this->mPlayerData->state->Update(dt);
		}
		for each (Bullet* bullet in bulletlist)
		{
			if (mPlayerData->state->GetState() != PlayerState::Clinging)
			{
				if (mPlayerData->player->GetReverse())
					bullet->Update(dt, this->getCurrentAnimation()->GetPosition() - D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2, -5, 0), true);
				else
					bullet->Update(dt, this->getCurrentAnimation()->GetPosition() + D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2, 5, 0), false);
			}
			else
				if (mPlayerData->player->GetReverse())
					bullet->Update(dt, this->getCurrentAnimation()->GetPosition() + D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2, -5, 0), false);
				else
					bullet->Update(dt, this->getCurrentAnimation()->GetPosition() - D3DXVECTOR3((this->getCurrentAnimation()->GetWidth() / 2), 5, 0), true);
		}
		Entity::Update(dt);
	}
	
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->HandleKeyboard(keys);
    }
	if(bulletlist.size()!=0)
	bulletlist.at(0)->HandleKeyboard(keys);
}

void Player::OnKeyPressed(int key)
{
	switch (key)
	{
		case VK_SPACE:
			{
				if (allowJump)
				{
					if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
					{
						Sound::getInstance()->play("Jump", false, 1);
						this->SetState(new PlayerJumpingState(this->mPlayerData));
					}
					allowJump = false;
				}
				if (mCurrentState == PlayerState::Clinging)
				{
					Sound::getInstance()->play("Jump", false, 1);
					this->SetState(new PlayerClingingJState(this->mPlayerData));
				}
				break;
			}
		case 0x58:
		{
			isGetOutGunAnimation = true;
			if (allowshoot)
			{
				Sound::getInstance()->play("shoot", false, 1);
				if (this->mPlayerData->player->getState() != PlayerState::BeDame){
					if (mPlayerData->player->GetReverse())
					{
						Bullet* bullet = new Bullet(this->getCurrentAnimation()->GetPosition() - D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2 - 10,100,0), true);
						bulletlist.insert(bulletlist.begin(), 1, bullet);
					}
					else
					{
						Bullet* bullet = new Bullet(this->getCurrentAnimation()->GetPosition() + D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2 + 10, -100, 0), false);
						bulletlist.insert(bulletlist.begin(), 1, bullet);
					}
				allowshoot = false;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void Player::OnKeyUp(int key)
{
    if (key == VK_SPACE)
        allowJump = true;
	if (key == 0x58) {
		allowshoot = true;
		isGetOutGunAnimation = false;
	}
}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

bool Player::GetReverse()
{
	return mCurrentReverse;
}

int Player::getHealthPoint()
{
	return HealthPoint;
}


void Player::setHealthPoint(Entity::EntityTypes entityTypes,bool isEnemy)
{
	int healthDown = 0;
	switch (entityTypes)
	{
	case Entity::EntityTypes::Gunner:
		healthDown = 1;
		break;
	case Entity::EntityTypes::HeadGunner:
		healthDown = 2;
		break;
	case Entity::EntityTypes::Helit:
		healthDown = 3;
		break;
	case Entity::EntityTypes::EnemyBullets1:
		healthDown = 1;
		break;
	case Entity::EntityTypes::EnemyBullets2:
		healthDown = 2;
		break;
	case Entity::EntityTypes::Genjibo:
		healthDown = 4;
		break;
	case Entity::EntityTypes::Byte:
		healthDown = 4;
		break;
	case Entity::EntityTypes::HornetBoss:
		healthDown = 5;
		break;
	default:
		break;
	}
	if (isEnemy == true) {
		healthDown++;
	}
	this->HealthPoint -= healthDown;
}



void Player::spawning()
{
	if (this->posY < 1320)
		posY += 10;
}

vector<Bullet*> Player::getbulletlist()
{
	return this->bulletlist;
}

void Player::deletebullet()
{
	this->bulletlist.pop_back();
}

PlayerData * Player::getplayerdata()
{
	return mPlayerData;
}

void Player::SetCamera(Camera *camera)
{
    this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		if (isAlive) {
			mCurrentAnimation->FlipVertical(mCurrentReverse);
			mCurrentAnimation->SetPosition(this->GetPosition());
			if (mPlayerData->state->GetState() == PlayerState::Spawning)
				this->spawning();
			mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			for each (Bullet* bullet in bulletlist)
			{
				bool reverse = mPlayerData->player->GetReverse();
				bullet->Draw(bullet->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey, reverse);
			}
			if (mPlayerData->state->GetState() == PlayerState::Dash || mPlayerData->state->GetState() == PlayerState::DashShoot) {
				for (int i = 0; i < sizeof(mlistFlashEffect); i++) {
					mlistFlashEffect[i].Draw(mPlayerData->player->GetReverse(), trans);
				}
				for (int i = 0; i < sizeof(mlistSmokeEffect); i++) {
					mlistSmokeEffect[i].Draw(mPlayerData->player->GetReverse(), trans);
				}
			}
			
			else
			{
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
			}
		}
		else {
			this->mPlayerData->state->Draw(trans);
		}
		if (hornetHP)
			hornetHP->Draw();
		if (byteHP)
			byteHP->Draw();
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;

	delete this->mPlayerData->state;
	this->mPlayerData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}


void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mPlayerData->state->OnCollision(impactor, side, data);
	if (impactor->Tag == Entity::Elevator && side == SideCollisions::Bottom) {
		this->mPlayerData->player->AddPosition(0, data.RegionCollision.top - data.RegionCollision.bottom + 2);
	}
	//Nếu nhân vật đang đứng im trên tháng máy mà ko chịu xuống , khi thang máy đâm vào tường phía trên thì nhân vật bị văng ra 
	if (mCurrentState == PlayerState::Standing) {
		if (impactor->Tag == Entity::Static && side == SideCollisions::Top) {
			if (this->mPlayerData->player->GetReverse() == false) {
				this->mPlayerData->player->AddPosition(5, 0);
			}
			else {
				this->mPlayerData->player->AddPosition(-5, 0);
			}
		}
	}

	
}

void Player::OnCollision(Entity * impactor, Entity::SideCollisions side)
{
	D3DXVECTOR2 pos(this->GetPosition().x, this->GetPosition().y);
	if (impactor->Tag == Entity::EntityTypes::EnemyBullets2) {
		if (this->isAlive == true && this->isBeforeDeath == false) {
			if (this->isTimeNoDame == false) {
				this->SetState(new PlayerDameState(this->getplayerdata()));
				if (this->isSetHealth == true || this->getHealthPoint() == 16) {
					this->setHealthPoint(impactor->Tag, false);
					this->isSetHealth = false;
				}
			}
			if (this->getHealthPoint() <= 0) {
				this->SetState(new PlayerDeathState(mPlayerData,pos.x, pos.y));
				this->isBeforeDeath = true;
			}
		}
	}
	
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}
void Player::noDameChangeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Running:
		mCurrentAnimation = mAnimationNoDameRun;
		break;

	case PlayerState::Standing:
		mCurrentAnimation = mAnimationNoDameStand;
		break;
	case PlayerState::Falling:
		mCurrentAnimation = mAnimationNoDameJumping;
		break;

	case PlayerState::Jumping:
		mCurrentAnimation = mAnimationNoDameJumping;
		break;
	case PlayerState::Clinging:
		mCurrentAnimation = mAnimationNoDameClinging;
		break;
	case PlayerState::ClingingJ:
		mCurrentAnimation = mAnimationNoDameClingingJ;
		break;
	case PlayerState::Dash:
		mCurrentAnimation = mAnimationNoDameDashing;
		break;
	case PlayerState::StandShoot:
		mCurrentAnimation = mAnimationNoDameStandShoot;
		break;
	case PlayerState::JumpShoot:
		mCurrentAnimation = mAnimationNoDameJumpShoot;
		break;
	case PlayerState::RunnShoot:
		mCurrentAnimation = mAnimationNoDameRunnShoot;
		break;
	case PlayerState::DashShoot:
		mCurrentAnimation = mAnimationNoDameDashShoot;
		break;
	case PlayerState::ClingingShoot:
		mCurrentAnimation = mAniamtionNoDameClingShoot;
		break;
	case PlayerState::ClingingJShoot:
		mCurrentAnimation = mAnimationNoDameClingJShoot;
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
        case PlayerState::Running:
            mCurrentAnimation = mAnimationRunning;
            break;

        case PlayerState::Standing:
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
            break;

        case PlayerState::Jumping:
            mCurrentAnimation = mAnimationJumping;
            break;
		case PlayerState::Spawning:
			mCurrentAnimation = mAnimationSpawning;
			break;
		case PlayerState::Clinging:
			mCurrentAnimation = mAnimationClinging;
			break;
		case PlayerState::ClingingJ:
			mCurrentAnimation = mAnimationClingingJ;
			break;
		case PlayerState::Dash:
			Sound::getInstance()->play("Dass", false, 1);
			mCurrentAnimation = mAnimationDashing;
			break;
		case PlayerState::StandShoot:
			mCurrentAnimation = mAnimationStandShoot;
			break;
		case PlayerState::JumpShoot:
			mCurrentAnimation = mAnimationJumpShoot;
			break;
		case PlayerState::RunnShoot:
			mCurrentAnimation = mAnimationRunnShoot;
			break;
		case PlayerState::DashShoot:
			mCurrentAnimation = mAnimationDashShoot;
			break;
		case PlayerState::ClingingShoot:
			mCurrentAnimation = mAniamtionClingShoot;
			break;
		case PlayerState::ClingingJShoot:
			mCurrentAnimation = mAnimationClingJShoot;
			break;
		case PlayerState::BeDame:
			mCurrentAnimation = mAniamtionBeDame;
			break;
		case PlayerState::Death:
			Sound::getInstance()->stop("background");
			Sound::getInstance()->play("Die", false, 1);
			mCurrentAnimation = mAnimationBeforeDeath;
			break;
        default:
            break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Animation * Player::getCurrentAnimation()
{
	return mCurrentAnimation;
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }
    return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
    if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && mCurrentState!= PlayerState::Clinging && mCurrentState != PlayerState::ClingingJ  && mCurrentState!=PlayerState::BeDame && mCurrentState!=PlayerState::Death)
    {
        this->SetState(new PlayerFallingState(this->mPlayerData));
    }    
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}