#include "../Entity.h"
#include "../../GameComponents/Animation.h"

class PlayerEffect : public Entity {
public:
	PlayerEffect();
	~PlayerEffect();
	void Update(float dt, D3DXVECTOR3 pos, bool isreverse);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool isreverse = false);
protected:
	Animation *mPlayerEffectDash;
	bool isreverse = false;
	D3DXVECTOR2 trans;
};