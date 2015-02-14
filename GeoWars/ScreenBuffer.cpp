#include <stdlib.h>
#include "ScreenBuffer.h"
#include "ASCII.h"

ScreenBuffer::ScreenBuffer()
{
	Move_To(160, 120);
	buffer = (uint16_t*)malloc(sizeof(uint16_t) * 5);
	lcd = new LCD_HY28B(LCD_RST, LCD_BL_CTRL);
	lcd->Set_Font(&ASCII);
}

ScreenBuffer::~ScreenBuffer()
{
}

uint16_t* ScreenBuffer::Buffer()
{
	return buffer;
}

void ScreenBuffer::Move_To(uint16_t x, uint16_t y)
{
	uint16_t r = sideLength / 2; // 'radius' of buffer.

	if (x < r)
		xPos = r;
	else if (x > LCD_X - (r + 1))
		xPos = LCD_X - (r + 1);
	else
		xPos = x;

	if (y < r)
		yPos = r;
	else if (y > LCD_Y - (r + 1))
		yPos = LCD_Y - (r + 1);
	else
		yPos = y;
}

uint16_t ScreenBuffer::X_Pos()
{
	return xPos;
}

uint16_t ScreenBuffer::Y_Pos()
{
	return yPos;
}

uint16_t ScreenBuffer::Side_Length()
{
	return sideLength;
}

void ScreenBuffer::Set_Side_Length(uint16_t sideLength)
{
	if (sideLength % 2) // Make sure sideLength is odd.
	{
		this->sideLength = sideLength;
	}
	else
	{
		this->sideLength = sideLength + 1;
	}

	size = sideLength * sideLength;
	buffer = (uint16_t*)realloc(buffer, sizeof(uint16_t) * size);
	Clear();
}

void ScreenBuffer::Read_LCD()
{
	for (int i = 0; i < sideLength; i++)
	{
		for (int j = 0; j < sideLength; j++)
		{
			buffer[i * sideLength + j] = lcd->Read_Pixel(j + xPos - (sideLength / 2), i + yPos - (sideLength / 2));
		}
	}
}

void ScreenBuffer::Render_To_LCD()
{
	lcd->Draw_Buffer(buffer, size, xPos, yPos);
	Clear();
}

/*#########################################################################
#							Private Functions 							  #
######################################################################## */

void ScreenBuffer::Clear()
{
	for (int i = 0; i < size; i ++)
	{
		buffer[i] = 0;
	}
}
