#include "GameObjectManager.h"
#include "Game.h"
#include "Distance.h"

uint32_t GameObjectManager::ID = 0;


GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

std::vector<GameObject*>::iterator GameObjectManager::Find_Object(uint32_t objectID)
{
	std::vector<uint32_t>::iterator itr = gameObjectID.begin();
	while (*itr != objectID && itr != gameObjectID.end())
	{
		itr++;
	}
	return gameObjects.begin() + std::distance(gameObjectID.begin(), itr);
}
 
void GameObjectManager::Add(GameObject* gameObject)
{
	gameObject->Set_ID(ID);
	gameObjects.push_back(gameObject);
	gameObjectID.push_back(GameObjectManager::ID);
	GameObjectManager::ID++;
}

void GameObjectManager::Remove(uint32_t objectID)
{
	std::vector<GameObject*>::iterator object;
	std::vector<uint32_t>::iterator ID;

	object = Find_Object(objectID);
	ID = gameObjectID.begin() + std::distance(gameObjects.begin(), object);

	delete *object;
	gameObjects.erase(object);
	gameObjectID.erase(ID);
}

GameObject* GameObjectManager::Get_GameObject(uint32_t objectID)
{
	std::vector<GameObject*>::iterator itr = Find_Object(objectID);
	return *itr;
}

std::vector<GameObject*>* GameObjectManager::Get_GameObjects()
{
	return &gameObjects;
}

void GameObjectManager::Update_All(uint32_t elapsedTime)
{
	std::vector<GameObject*>::iterator object = gameObjects.begin();
	uint16_t vectorSize = gameObjects.size();
	uint16_t loopCount = 0;

	while (object != gameObjects.end() && loopCount != vectorSize)
	{
		/* If vector is reallocated itorators are invalidated.
		 * During Update, objects can be created or removed. Check if current size of vector
		 * matches the size at the start of the loop.
		 */
		if (gameObjects.size() == vectorSize)
		{
			(*object)->Update(elapsedTime);
		}
		else
		{
			vectorSize = gameObjects.size();
			object = gameObjects.begin() + loopCount; // If size changes, get new iterator.
			(*object)->Update(elapsedTime);
		}

		object++;
		loopCount++;
	}
}

void GameObjectManager::Draw_All(ScreenBuffer* screenBuffer)
{
	/* Loop over every game object. For each object, reposition screen buffer and draw all
	 * neccessary objects.
	 */
	std::vector<GameObject*>::const_iterator object = gameObjects.begin();
	while (object != gameObjects.end())
	{
		// Added constant is padding pixels around sprite.
		screenBuffer->Set_Side_Length((*object)->Sprite_Size() + 8);
		screenBuffer->Move_To((*object)->X_Pos(), (*object)->Y_Pos());

		// Only draw game objects within a certain distance of the screen buffer.
		std::vector <GameObject*>::iterator object2 = gameObjects.begin();
		while (object2 != gameObjects.end())
		{
			uint16_t dist = Distance_2D((*object2)->X_Pos(), (*object2)->Y_Pos(),
										screenBuffer->X_Pos(), screenBuffer->Y_Pos());

			if (dist < screenBuffer->Side_Length())
			{
				(*object2)->Draw(screenBuffer);
			}
			object2++;
		}
		screenBuffer->Render_To_LCD();

		object++;
	}
}
