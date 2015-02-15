#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include <vector>
#include "GameObject.h"
#include "ScreenBuffer.h"
#include "Thumbstick.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	std::vector<GameObject*>::iterator Find_Object(uint32_t objectID);
	void Add(GameObject* gameObject);
	void Remove(uint32_t objectID);
	GameObject* Get_GameObject(uint32_t objectID);
	std::vector<GameObject*>* Get_GameObjects();
	std::vector<uint32_t>* Get_GameObject_IDs();
	uint32_t Num_Objects();

	void Update_All(uint32_t elapsedTime);
	void Draw_All(ScreenBuffer* _screenbuffer);

private:
	std::vector <GameObject*> gameObjects;
	std::vector <uint32_t> gameObjectIDs;

	static uint32_t ID;
	static uint32_t numObjects;
};

#endif // _GAME_OBJECT_MANAGER_H_