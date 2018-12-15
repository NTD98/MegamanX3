#include "PlayerFlashDashEffect.h"

PlayerFlashDashEffect::PlayerFlashDashEffect()
{
	mPlayerFlashDash = new Animation("Resources/megaman/flashdash.png", 5, 1, 5, 0.05f);
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
		mPlayerFlashDash->Update(dt);
		mPlayerFlashDash->SetPosition(D3DXVECTOR3(pos.x - PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerFlashDash->GetHeight() / 2, 0));
	}
	else
	{

		mPlayerFlashDash->Update(dt);
		mPlayerFlashDash->SetPosition(D3DXVECTOR3(pos.x + PlayerSizeWidth / 2 , (pos.y + PlayerSizeHeight / 2) - mPlayerFlashDash->GetHeight() / 2, 0));
	}
}

void PlayerFlashDashEffect::Draw(bool isreverse , D3DXVECTOR2 Trans)
{
	mPlayerFlashDash->FlipVertical(isreverse);
	if (isreverse)
	{
		mPlayerFlashDash->Draw(Trans);
		isreverse = false;
	}
	else
	{
		mPlayerFlashDash->Draw(Trans);
		isreverse = true;
	}
}




