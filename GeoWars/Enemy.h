#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	void Update(uint16_t elapsedTime);

	bool Hit_Player();

private:
	uint16_t speed;
};

#endif // _ENEMY_H_
