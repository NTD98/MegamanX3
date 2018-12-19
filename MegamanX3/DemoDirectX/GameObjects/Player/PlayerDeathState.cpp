#include "PlayerDeathState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"

PlayerDeathState::PlayerDeathState(PlayerData *playerData,float posX,float posY)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetPosition(posX, posY);
	

	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, 0,1 ));

	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, -30,2));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 30, 0,2));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, 30,2));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -30, 0,2));

	mListDeathCircle.push_back(new DeathCircle(posX, posY, 20, -20,3));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 20, 20,3));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -20, 20,3));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -20, -20,3));

	mListDeathCircle.push_back(new DeathCircle(posX, posY, 50, -50,4));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 50, 50,4));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -50, 50,4));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -50, -50,4));

	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, -70,5));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 70, 0,5));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, 70,5));
	mListDeathCircle.push_back(new DeathCircle(posX, posY, -70, 0,5));
	
	dtTimeBeforeDeath = 0;
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float dt)
{
	dtTimeBeforeDeath += dt;
	if (dtTimeBeforeDeath >= 1.0f) {
		this->mPlayerData->player->isAlive = false;
		this->isTanBien = true;
		for (int i = 0; i < mListDeathCircle.size(); i++) {
			mListDeathCircle[i]->Update(dt);
		}
	}
}

void PlayerDeathState::Draw(D3DXVECTOR2 transform)
{
	if (this->isTanBien == true) {
		for (int i = 0; i < mListDeathCircle.size(); i++) {
			mListDeathCircle[i]->Draw(transform);
		}
	}
}

PlayerState::StateName PlayerDeathState::GetState()
{
	return PlayerState::Death;
}

