#pragma once
class EnemyState;
class Enemy;

class EnemyData
{
public:
	EnemyData();
	~EnemyData();

	Enemy      *Enemy;
	EnemyState *state;

protected:

};

