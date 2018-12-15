#include "PlayerSmokeDashEffect.h"

PlayerSmokeDashEffect::PlayerSmokeDashEffect()
{
	mPlayerSmokeDash = new Animation("Resources/megaman/smokedash.png", 9, 1, 9, 0.1f);
}

PlayerSmokeDashEffect::~PlayerSmokeDashEffect()
{

}



void PlayerSmokeDashEffect::Update(float dt, D3DXVECTOR3 pos, bool isreverse, int PlayerSizeWidth, int PlayerSizeHeight)
{

	if (isreverse == false)
	{
		mPlayerSmokeDash->Update(dt);
		mPlayerSmokeDash->SetPosition(D3DXVECTOR3(pos.x - PlayerSizeWidth / 2, (pos.y + PlayerSizeHeight / 2) - mPlayerSmokeDash->GetHeight() / 2, 0));
	}
	else
	{

		mPlayerSmokeDash->Update(dt);
		mPlayerSmokeDash->SetPosition(D3DXVECTOR3(pos.x + PlayerSizeWidth / 2, (pos.y + PlayerSizeHeight / 2) - mPlayerSmokeDash->GetHeight() / 2, 0));
	}
}

void PlayerSmokeDashEffect::Draw(bool isreverse, D3DXVECTOR2 Trans)
{
	mPlayerSmokeDash->FlipVertical(isreverse);
	if (isreverse)
	{
		mPlayerSmokeDash->Draw(Trans);
		isreverse = false;
	}
	else
	{
		mPlayerSmokeDash->Draw(Trans);
		isreverse = true;
	}
}




