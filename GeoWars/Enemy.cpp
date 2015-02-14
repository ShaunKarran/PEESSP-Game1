#include "Enemy.h"
#include "Game.h"
#include "Distance.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(uint16_t elapsedTime)
{
	double someScale = 1000;
	double deltaX, deltaY, xVel, yVel;
	GameObject* player = Game::Get_GameObjectManager()->Get_GameObject(0); // Player ID = 0.

	double targetX = player->X_Pos();
	double targetY = player->Y_Pos();

	xVel = (targetX - xPos) / someScale;
	yVel = (targetY - yPos) / someScale;

	Set_Velocity(xVel, yVel);

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
