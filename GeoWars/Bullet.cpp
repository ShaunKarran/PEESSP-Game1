#include "Bullet.h"
#include "Game.h"
#include "Distance.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{
}

void Bullet::Update(uint16_t elapsedTime)
{
	uint32_t enemyID;

	GameObject::Update(elapsedTime);

	if (!Is_On_Screen())
	{
		Game::Get_GameObjectManager()->Remove(ID);
	}
	else if (Hit_Enemy(&enemyID))
	{
		Set_Dead();
		Game::Get_GameObjectManager()->Get_GameObject(enemyID)->Set_Dead();
	}
}

bool Bullet::Hit_Enemy(uint32_t* enemyID)
{
	uint16_t distance;
	std::vector<GameObject*>* gameObjects = Game::Get_GameObjectManager()->Get_GameObjects();
	std::vector<GameObject*>::iterator itr = gameObjects->begin() + 1; // +1 to skip player.

	while (itr != gameObjects->end())
	{
		distance = Distance_2D(xPos, yPos, (*itr)->X_Pos(), (*itr)->Y_Pos());
		if (distance != 0 && distance < 5) // Checks distance to itself, so ignore result of 0.
		{
			*enemyID = (*itr)->Get_ID();
			return true;
		}
		itr++;
	}
	return false;
}
