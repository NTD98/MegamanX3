#include "../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"


class DeathCircle : public Entity
{
public:
	~DeathCircle();
	DeathCircle(float posX, float posY, float vx, float vy);
	void Update(float dt);
	//void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
protected:
	Animation* mAnimation;
	float posX1, posY1;
};
