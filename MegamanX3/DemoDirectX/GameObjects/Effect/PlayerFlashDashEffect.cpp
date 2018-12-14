#include "PlayerFlashDashEffect.h"

PlayerEffect::PlayerEffect()
{
	mPlayerEffectDash = new Animation("Resources/megaman/EffectDash.png", 5, 1, 5, 0.05f);
}

PlayerEffect::~PlayerEffect()
{

}

void PlayerEffect::SetPos(float posX,float posY)
{
	this->SetPosition(posX,posY);
}

void PlayerEffect::Update(float dt, D3DXVECTOR3 pos, bool isreverse, int PlayerSizeWidth, int PlayerSizeHeight)
{
	if (isreverse == false)
	{
		mPlayerEffectDash->Update(dt);
		mPlayerEffectDash->SetPosition(D3DXVECTOR3(pos.x - PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerEffectDash->GetHeight() / 2, 0));
	}
	else
	{

		mPlayerEffectDash->Update(dt);
		mPlayerEffectDash->SetPosition(D3DXVECTOR3(pos.x + PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerEffectDash->GetHeight() / 2, 0));
	}
}

void PlayerEffect::Draw(bool isreverse , D3DXVECTOR2 Trans)
{
	mPlayerEffectDash->FlipVertical(isreverse);
	if (isreverse)
	{
		mPlayerEffectDash->Draw(Trans);
		isreverse = false;
	}
	else
	{
		mPlayerEffectDash->Draw(Trans);
		isreverse = true;
	}
}




