#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "DeathCircle.h"

class PlayerDeathEffect : public Entity
{
public:
	~PlayerDeathEffect();
	PlayerDeathEffect(float posX, float posY);
	void Update(float dt);
	void Draw(D3DXVECTOR2 transform);
protected:
	std::vector<Animation*> mListAnimation;
	std::vector<DeathCircle*> mListDeathCircle;
	float vx, vy;
};
