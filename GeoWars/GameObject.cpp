#include <stdlib.h>
#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	xPos = 0;
	yPos = 0;
	xVelocity = 0;
	yVelocity = 0;
	maxVelocity = 10;
	hasSprite = false;
	isDead = false;
	rm = false;
}

GameObject::~GameObject()
{
}

void GameObject::Set_ID(uint32_t ID)
{
	this->ID = ID;
}

uint32_t GameObject::Get_ID()
{
	return ID;
}

void GameObject::Set_Dead()
{
	isDead = true;
}

bool GameObject::Is_Dead()
{
	return isDead;
}

void GameObject::Move(double x, double y)
{
	xPos += x;
	yPos += y;
}

double GameObject::X_Pos()
{
	return xPos;
}

double GameObject::Y_Pos()
{
	return yPos;
}

void GameObject::Sprite(const uint16_t* sprite)
{
	this->sprite = sprite;
	hasSprite = true;
	spriteWidth = sprite[0];
	spriteHeight = sprite[1];
}

uint8_t GameObject::Sprite_Size()
{
	if (spriteWidth > spriteHeight)
	{
		return spriteWidth;
	}
	else
	{
		return spriteHeight;
	}
}

bool GameObject::Is_On_Screen()
{
	if (xPos < -10 || xPos > 330 || yPos < -10 || yPos > 250)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameObject::Update(uint16_t elapsedTime)
{
	if (rm)
	{
		Game::Get_GameObjectManager()->Remove(ID);
	}
	else
	{
		double deltaX, deltaY;

		deltaX = xVelocity * ((double)elapsedTime / 1000);
		deltaY = yVelocity * ((double)elapsedTime / 1000);
		Move(deltaX, deltaY);
	}
}

void GameObject::Draw(ScreenBuffer* screenBuffer)
{
	if (isDead)
	{
		rm = true;
	}
	else if (hasSprite)
	{
		// Sprite x and y position relative to the screenBuffer postion.
		int16_t spriteRelX = xPos - screenBuffer->X_Pos() + (screenBuffer->Side_Length() / 2);
		int16_t spriteRelY = yPos - screenBuffer->Y_Pos() + (screenBuffer->Side_Length() / 2);

		uint16_t width = sprite[0];
		uint16_t height = sprite[1];
		// The buffer position that matches with the first sprite pixel.
		// Negative numbers mean the sprite starts off of the buffer, and will be ignored later.
		int16_t bufferStartPos = (spriteRelY - (height / 2)) * screenBuffer->Side_Length()
								 + (spriteRelX - (width / 2));

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int16_t bufferPos = bufferStartPos + i * screenBuffer->Side_Length() + j;
				if (bufferPos >= 0 								// Pixel is inside buffer.
					&& bufferPos < (screenBuffer->Side_Length() * screenBuffer->Side_Length())
					&& j >= width / 2 - spriteRelX 				// Pixel is not off left edge of buffer.
					&& j < screenBuffer->Side_Length() + width / 2 - spriteRelX	// Pixel is not off right edge of buffer.
					&& sprite[2 + i * width + j] != 0x0000) 	// Dont draw black pixels. Psuedo alpha.
				{
					screenBuffer->Buffer()[bufferPos] = sprite[2 + i * width + j];
				}
			}
		}
	}
}

void GameObject::Set_Velocity(double xVel, double yVel)
{
	if (abs(xVel) <= maxVelocity)
	{
		xVelocity = xVel;
	}
	else if (xVel > maxVelocity)
	{
		xVelocity = maxVelocity;
	}
	else if (-xVel > maxVelocity)
	{
		xVelocity = -maxVelocity;
	}

	if (abs(yVel) <= maxVelocity)
	{
		yVelocity = yVel;
	}
	else if (yVel > maxVelocity)
	{
		yVelocity = maxVelocity;
	}
	else if (-yVel > maxVelocity)
	{
		yVelocity = -maxVelocity;
	}
}

void GameObject::Set_Max_Velocity(double maxVel)
{
	maxVelocity = maxVel;
}
