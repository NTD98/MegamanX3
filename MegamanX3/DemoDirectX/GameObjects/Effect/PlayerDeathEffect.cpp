#include "PlayerDeathEffect.h"

PlayerDeathEffect::~PlayerDeathEffect()
{
}

PlayerDeathEffect::PlayerDeathEffect(float posX, float posY)
{
	this->SetPosition(posX, posY);
	for (int i = 0; i < 16; i++) {
		if (i == 0)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, -70));
		if (i == 1)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 70, 0));
		if (i == 2)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, 70));
		if (i == 3)	mListDeathCircle.push_back(new DeathCircle(posX, posY, -70, 0));
		if (i == 4)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 20, -20));
		if (i == 5)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 20, 20));
		if (i == 6)	mListDeathCircle.push_back(new DeathCircle(posX, posY, -20, 20));
		if (i == 7)	mListDeathCircle.push_back(new DeathCircle(posX, posY, -20, -20));
		if (i == 8)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, -30));
		if (i == 9)	mListDeathCircle.push_back(new DeathCircle(posX, posY, 30, 0));
		if (i == 10)mListDeathCircle.push_back(new DeathCircle(posX, posY, 0, 30));
		if (i == 11)mListDeathCircle.push_back(new DeathCircle(posX, posY, -30, 0));
		if (i == 12)mListDeathCircle.push_back(new DeathCircle(posX, posY, 50, -50));
		if (i == 13)mListDeathCircle.push_back(new DeathCircle(posX, posY, 50, 50));
		if (i == 14)mListDeathCircle.push_back(new DeathCircle(posX, posY, -50, 50));
		if (i == 15)mListDeathCircle.push_back(new DeathCircle(posX, posY, -50, -50));
	}

}

void PlayerDeathEffect::Update(float dt)
{
	for (int i = 0; i < mListDeathCircle.size(); i++) {
		mListDeathCircle[i]->Update(dt);
	}
}

void PlayerDeathEffect::Draw(D3DXVECTOR2 transform)
{
	for (int i = 0; i < mListDeathCircle.size(); i++) {
		mListDeathCircle[i]->Draw(transform);
	}
}
