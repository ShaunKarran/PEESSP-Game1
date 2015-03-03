#include <WProgram.h>
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

uint16_t Player::timeSinceFired;
uint16_t Player::bombCooldown;

Player::Player()
{
	spawnTimer = 0;
	timeSinceFired = 0;
	bombsRemaining = 3;
	bombCooldown = 5000;
}

Player::~Player()
{
}

void Player::Set_Thumbsticks(Thumbstick* left, Thumbstick* right)
{
	leftThumbstick = left;
	rightThumbstick = right;
}

void Player::Fire_Rate(uint16_t fireRate)
{
	this->fireRate = fireRate;
}

void Player::Update(uint16_t elapsedTime)
{
	double adcScale = 0.1; // So scale down the magnitude of the ts position.
	double deltaX, deltaY, xVel, yVel;
	int16_t leftThumbstickX, leftThumbstickY;

	if (isDead)
	{
		if (spawnTimer > 3000)
		{
			spawnTimer = 0;
			isDead = false;
			rm = false;
			xPos = random(0, 340);
			yPos = random(0, 240);
		}
		else
		{
			spawnTimer += elapsedTime;
		}
		return;
	}

	leftThumbstick->Position(&leftThumbstickX, &leftThumbstickY); // Read thumbstick positions.

	// Move player based on left thumbstick position.
	xVel = leftThumbstickX * adcScale; // Scale ts position to meaningful velocity value.
	yVel = -leftThumbstickY * adcScale; // Negative value. Top of screen is smaller y values.

	Set_Velocity(xVel, yVel); // Add velocity to state and check limits of velocity.

	deltaX = xVelocity * ((double)elapsedTime / 1000);
	deltaY = yVelocity * ((double)elapsedTime / 1000);

	Move(deltaX, deltaY);

	if (fireRate < timeSinceFired)
	{
		Fire();
		timeSinceFired = 0;
	}
	else
	{
		timeSinceFired += elapsedTime;
	}

	bombCooldown = (bombCooldown > 0) ? bombCooldown - elapsedTime : 0;

	if (bombsRemaining > 0 && bombCooldown == 0 && rightThumbstick->Is_Pressed())
	{
		Detonate_Bomb();
		bombsRemaining--;
		bombCooldown = 5000;
	}
	
	hasBeenDrawn = false;
}

void Player::Fire()
{
	int16_t rightThumbstickX, rightThumbstickY;

	rightThumbstick->Position(&rightThumbstickX, &rightThumbstickY);

	if (abs(rightThumbstickX) > 500 || abs(rightThumbstickY) > 500)
	{
		double magnitude = sqrt((rightThumbstickX * rightThumbstickX) + (rightThumbstickY * rightThumbstickY));
		double xDirection = rightThumbstickX / magnitude;
		double yDirection = rightThumbstickY / magnitude;

		Bullet* bullet = new Bullet();
		bullet->Set_Type(Bullet::STANDARD);
		bullet->Move(xPos, yPos);
		bullet->Set_Velocity(xDirection, -yDirection); // Negative for screen values.
		Game::Get_GameObjectManager()->Add(bullet);
	}
}

void Player::Detonate_Bomb()
{
	std::vector<uint32_t>* gameObjectIDs = Game::Get_GameObjectManager()->Get_GameObject_IDs();
	std::vector<uint32_t>::iterator itr = gameObjectIDs->begin() + 1;

	while (itr != gameObjectIDs->end())
	{
		Game::Get_GameObjectManager()->Get_GameObject(*itr)->Set_Dead();
		itr++;
	}
}
