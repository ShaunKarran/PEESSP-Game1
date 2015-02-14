#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Update(uint16_t elapsedTime);

	bool Hit_Enemy(uint32_t* enemyID);

private:
	uint8_t damage;
};

#endif // _BULLET_H_
