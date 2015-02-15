#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Thumbstick.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Set_Thumbsticks(Thumbstick* left, Thumbstick* right);
	void Fire_Rate(uint16_t fireRate);

	void Update(uint16_t elapsedTime);

	void Fire();
	void Detonate_Bomb();

private:
	Thumbstick* leftThumbstick;
	Thumbstick* rightThumbstick;

	uint16_t spawnTimer;

	uint16_t fireRate;
	static uint16_t timeSinceFired;
	uint8_t bombsRemaining;
	static uint16_t bombCooldown;
};

#endif // _PLAYER_H_
