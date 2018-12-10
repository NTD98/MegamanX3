#include "PlayerEffect.h"

PlayerEffect::PlayerEffect()
{
	mPlayerEffectDash = new Animation("Resources/megaman/EffectDash.png", 5, 1, 5, 0.05f);

}

PlayerEffect::~PlayerEffect()
{
	delete this;
}

void PlayerEffect::Update(float dt, D3DXVECTOR3 pos, bool isreverse)
{
	if (isreverse == false)
	{
		mPlayerEffectDash->SetPosition(D3DXVECTOR3(pos.x + 20, pos.y, 0));
		this->SetPosition(pos.x,pos.y);
	}
	else
	{
		mPlayerEffectDash->SetPosition(D3DXVECTOR3(pos.x -20, pos.y, 0));
		this->SetPosition(pos.x, pos.y);
	}
}

void PlayerEffect::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey, bool isreverse)
{
	if (isreverse == false)
	{
		mPlayerEffectDash->Draw(D3DXVECTOR3(position.x + 2, position.y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
		isreverse = false;
	}
	else
	{
		mPlayerEffectDash->Draw(D3DXVECTOR3(position.x - 2, position.y, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
		isreverse = true;
	}
}




