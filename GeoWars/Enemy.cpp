#include <WProgram.h>
#include <math.h>
#include "Enemy.h"
#include "Game.h"
#include "Helpers.h"

Enemy::Enemy()
{
	speed = 75;
	maxVelocity = 75;
}

Enemy::~Enemy()
{
}

void Enemy::Update(uint16_t elapsedTime)
{
	double targetX, targetY, xVel, yVel, vectorMag;
	GameObject* player = Game::Get_GameObjectManager()->Get_GameObject(0); // Player ID = 0.

	if (player->Is_Dead())
	{
		targetX = random(-50, 51);
		targetY = random(-50, 51);
		vectorMag = sqrt(targetX * targetX + targetY * targetY) + 1; // Really shouldnt ever be 0, so add 1.
		xVel = targetX / vectorMag;
		yVel = targetY / vectorMag;
		Set_Velocity(xVel * speed, yVel * speed);
	}
	else
	{
		targetX = (player->X_Pos() - xPos) * ((double)random(0, 500) / 100);
		targetY = (player->Y_Pos() - yPos) * ((double)random(0, 500) / 100);
		vectorMag = sqrt(targetX * targetX + targetY * targetY);
		xVel = targetX / vectorMag;
		yVel = targetY / vectorMag;
		Set_Velocity(xVel * speed, yVel * speed);
	}

	GameObject::Update(elapsedTime);

	if (Hit_Player())
	{
		player->Set_Dead();
	}
}

bool Enemy::Hit_Player()
{
	uint16_t distance;
	GameObject* player = Game::Get_GameObjectManager()->Get_GameObject(0); // Player ID = 0.

	distance = Distance_2D(xPos, yPos, player->X_Pos(), player->Y_Pos());

	if (distance < 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}
