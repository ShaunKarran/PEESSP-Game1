#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>
#include <stdint.h>
#include "ScreenBuffer.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Set_ID(uint32_t ID);
	uint32_t Get_ID();
	void Set_Dead();
	void Move(double x, double y);
	double X_Pos();
	double Y_Pos();
	void Sprite(const uint16_t* sprite);
	uint8_t Sprite_Size();
	bool Is_On_Screen();
	void Draw(ScreenBuffer* screenBuffer);
	virtual void Update(uint16_t elapsedTime);
	
	void Set_Velocity(double xVel, double yVel);
	void Set_Max_Velocity(double maxVel);

protected:
	uint32_t ID;
	bool isDead;
	bool rm; // remove
	double xPos;
	double yPos;

	double xVelocity;
	double yVelocity;
	double maxVelocity;

	bool hasSprite;
	const uint16_t* sprite;
	uint8_t spriteWidth;
	uint8_t spriteHeight;
};

#endif // _GAMEOBJECT_H_
