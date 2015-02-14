#include <WProgram.h>
#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Sprites.h"

uint16_t Player::timeSinceFired;

Player::Player()
{
	spawnTimer = 0;
	timeSinceFired = 0;
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
	double someScale = 20000; // So scale down the magnitude of the ts position. Name is temporary.
	double deltaX, deltaY, xVel, yVel;
	int16_t leftThumbstickX, leftThumbstickY;

	if (rm)
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
	//leftThumbstickX = 1024; leftThumbstickY = 0; // For testing.

	// Move player based on left thumbstick position.
	xVel = leftThumbstickX / someScale; // Scale ts position to meaningful velocity value.
	yVel = -leftThumbstickY / someScale; // Negative value. Top of screen is smaller y values.
	Set_Velocity(xVel, yVel); // Add velocity to state and check limits of velocity.

	deltaX = xVelocity * elapsedTime;
	deltaY = yVelocity * elapsedTime;
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
}

void Player::Fire()
{
	int16_t rightThumbstickX, rightThumbstickY;

	rightThumbstick->Position(&rightThumbstickX, &rightThumbstickY);

	if (rightThumbstickX != 0 || rightThumbstickY != 0)
	{
		Bullet* bullet = new Bullet();
		bullet->Sprite(sprite_bullet);
		bullet->Move(xPos, yPos);
		bullet->Set_Max_Velocity(0.2);
		bullet->Set_Velocity(rightThumbstickX / 200, -rightThumbstickY / 200); // Negative for screen values.
		(Game::Get_GameObjectManager())->Add(bullet);
	}
}
