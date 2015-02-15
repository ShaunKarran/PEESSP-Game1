#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	enum bulletType_t { STANDARD };

	Bullet();
	~Bullet();

	void Set_Type(bulletType_t type);
	void Set_Velocity(double xVel, double yVel);
	void Update(uint16_t elapsedTime);

	bool Hit_Enemy(uint32_t* enemyID);

private:
	uint16_t speed;
};

#endif // _BULLET_H_
