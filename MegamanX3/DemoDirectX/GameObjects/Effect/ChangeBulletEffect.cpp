#include "ChangeBulletEffect.h"

ChangeBulletEffect::ChangeBulletEffect()
{
	//mPlayerFlashDash = new Animation("Resources/megaman/flashdash.png", 5, 1, 5, 0.05f);
	mEffectChangeBullet1 = new Animation("Resources/megaman/changeBullet1Effect.png", 15, 1, 15, 0.01f);
	mEffectChangeBullet2 = new Animation("Resources/megaman/changeBullet2Effect.png", 15, 1, 15, 0.01f);
	mCurrentAnimation = mEffectChangeBullet1;
}

ChangeBulletEffect::~ChangeBulletEffect()
{

}



void ChangeBulletEffect::Update(float dt, Player *mplayer)
{
	if( mplayer->dtChangBullet<1.5f) {
		mCurrentAnimation = mEffectChangeBullet1;
	}
	else {
		mCurrentAnimation = mEffectChangeBullet2;
	}
	mCurrentAnimation->Update(dt);
	mCurrentAnimation->SetPosition(mplayer->GetPosition());
	
}

void ChangeBulletEffect::Draw( D3DXVECTOR2 Trans)
{
	mCurrentAnimation->Draw(Trans);
}




