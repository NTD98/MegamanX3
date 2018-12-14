#include "PlayerFlashDashEffect.h"

PlayerFlashDashEffect::PlayerFlashDashEffect()
{
	mPlayerFlashDashEffectDash = new Animation("Resources/megaman/flashDash.png", 5, 1, 5, 0.05f);
}

PlayerFlashDashEffect::~PlayerFlashDashEffect()
{

}

void PlayerFlashDashEffect::SetPos(float posX,float posY)
{
	this->SetPosition(posX,posY);
}

void PlayerFlashDashEffect::Update(float dt, D3DXVECTOR3 pos, bool isreverse, int PlayerSizeWidth, int PlayerSizeHeight)
{
	if (isreverse == false)
	{
		mPlayerFlashDashEffectDash->Update(dt);
		mPlayerFlashDashEffectDash->SetPosition(D3DXVECTOR3(pos.x - PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerFlashDashEffectDash->GetHeight() / 2, 0));
	}
	else
	{

		mPlayerFlashDashEffectDash->Update(dt);
		mPlayerFlashDashEffectDash->SetPosition(D3DXVECTOR3(pos.x + PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerFlashDashEffectDash->GetHeight() / 2, 0));
	}
}

void PlayerFlashDashEffect::Draw(bool isreverse , D3DXVECTOR2 Trans)
{
	mPlayerFlashDashEffectDash->FlipVertical(isreverse);
	if (isreverse)
	{
		mPlayerFlashDashEffectDash->Draw(Trans);
		isreverse = false;
	}
	else
	{
		mPlayerFlashDashEffectDash->Draw(Trans);
		isreverse = true;
	}
}




