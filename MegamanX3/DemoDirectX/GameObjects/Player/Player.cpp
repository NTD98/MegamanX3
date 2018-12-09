#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSpawingState.h"
#include "PlayerStandingState.h"
#include "PlayerClingingState.h"
#include "PlayerClingingJState.h"
#include "PlayerDashState.h"
#include "PlayerStandShootState.h"
#include "PlayerJumpShootState.h"
#include "../../GameComponents/GameCollision.h"

float check = 0.0;
bool isDone = false;
Player::Player()
{
    mAnimationStanding = new Animation("Resources/megaman/standing.png", 3, 1,3 , 0.2f);
    mAnimationJumping = new Animation("Resources/megaman/pic3.png", 7, 1, 7, 0.1f);
    mAnimationRunning = new Animation("Resources/megaman/pic2.png", 11, 1, 11, 0.05f);
	mAnimationSpawning = new Animation("Resources/megaman/pic7.png", 7, 1, 7, 0.2f);	
	mAnimationStandShoot = new Animation("Resources/megaman/standShoot.png", 2, 1, 2, 0.5f);
	mAnimationJumpShoot = new Animation("Resources/megaman/JumpShoot.png", 6, 1, 6, 0.1f);
	mAnimationRunnShoot = new Animation("Resources/megaman/RunnShoot.png", 10, 1, 10, 0.1f);
	mAnimationDashShoot = new Animation("Resources/megaman/dashshoot.png", 2, 1, 2, 0.1f);
    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerSpawingState(this->mPlayerData));

    allowJump = true;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
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
				bullet->Update(dt, this->getCurrentAnimation()->GetPosition() + D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() /2, -5, 0), false);
			else
				bullet->Update(dt, this->getCurrentAnimation()->GetPosition() - D3DXVECTOR3((this->getCurrentAnimation()->GetWidth() / 2), 5, 0), true);
	}
    Entity::Update(dt);
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
					if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState==PlayerState::RunnShoot)
					{
						this->SetState(new PlayerJumpingState(this->mPlayerData));
					}
					
					allowJump = false;
				}
				if (mCurrentState == PlayerState::Clinging)
				{
					this->SetState(new PlayerClingingJState(this->mPlayerData));

				}
				break;
			}
		case 0x5A:
		{
			if (allowdash)
			{
				if (allowDashShoot) {
					allowActionAndShoot = true;
				}
				this->SetState(new PlayerDashState(this->mPlayerData));
				allowDashShoot=false;
				allowdash = false;
			}
			break;
		}
		case 0x58:
		{
			allowActionAndShoot = true;
			
			if (allowshoot)
			{
				if (mPlayerData->player->GetReverse())
				{
					Bullet* bullet = new Bullet(this->getCurrentAnimation()->GetPosition()-D3DXVECTOR3(this->getCurrentAnimation()->GetWidth()/2-10,100,0), true);
					bulletlist.insert(bulletlist.begin(), 1, bullet);
				}
				else
				{
					Bullet* bullet = new Bullet(this->getCurrentAnimation()->GetPosition()+ D3DXVECTOR3(this->getCurrentAnimation()->GetWidth() / 2+10,-100, 0), false);
					bulletlist.insert(bulletlist.begin(), 1, bullet);
				}
				
				allowshoot = false;
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
	if (key == 0x5A)
		allowdash = true;
	if (key == 0x58) {
		allowshoot = true;
		allowDashShoot = true;
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
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

    if (mCamera)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		if (mPlayerData->state->GetState() == PlayerState::Spawning)
			this->spawning();
        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
		for each (Bullet* bullet in bulletlist)
		{
			bool reverse = mPlayerData->player->GetReverse();
			bullet->Draw(bullet->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey);
		}
    }
    else
    {
        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
    }        
	
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;

	delete this->mPlayerData->state;
	this->mPlayerData->state = newState;
		if (allowActionAndShoot) {
			this->changeAnimation(newState->GetStateHaveShoot());
			allowActionAndShoot = false;
		}
		else {
			this->changeAnimation(newState->GetState());
		}
    mCurrentState = newState->GetState();
}


void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    this->mPlayerData->state->OnCollision(impactor, side, data);
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
			mAnimationClinging = new Animation("Resources/megaman/pic0.png", 3, 1, 3, 0.15f);
			mCurrentAnimation = mAnimationClinging;
			break;
		case PlayerState::ClingingJ:
			mAnimationClingingJ = new Animation("Resources/megaman/pic01.png", 2, 1, 2, 0.15f);
			mCurrentAnimation = mAnimationClingingJ;
			break;
		case PlayerState::Dash:
			mAnimationDashing = new Animation("Resources/megaman/dash.png", 2, 1, 2, 0.2f, D3DCOLOR_XRGB(0, 0, 0));
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
    if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && mCurrentState!= PlayerState::Clinging && mCurrentState != PlayerState::ClingingJ && mCurrentState !=PlayerState::StandShoot)
    {
        this->SetState(new PlayerFallingState(this->mPlayerData));
    }    
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}