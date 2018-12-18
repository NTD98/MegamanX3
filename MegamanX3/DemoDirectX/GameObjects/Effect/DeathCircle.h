#include "../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"


class DeathCircle : public Entity
{
public:
	~DeathCircle();
	DeathCircle(float posX, float posY, float vx, float vy,int Animation);
	void Update(float dt);
	void Draw(D3DXVECTOR2 transform);
protected:
	Animation* mAnimation1,
		*mAnimation2,
		*mAnimation3,
		*mAnimation4,
		*mAnimation5,
		*mCurrentAnimation;
	float posX1, posY1;
};
