#pragma once
#include "PlayerState.h"
#include "../Effect/DeathCircle.h"
class PlayerDeathState : public PlayerState
{
public:
	PlayerDeathState(PlayerData *playerData,float posX,float posY);
	~PlayerDeathState();
	void Update(float dt);
	void Draw(D3DXVECTOR2 transform);
	virtual StateName GetState();
protected:
	std::vector<Animation*> mListAnimation;
	std::vector<DeathCircle*> mListDeathCircle;
	float vx, vy;
	float dtTimeBeforeDeath;
	bool isTanBien = false;
};

#pragma once
