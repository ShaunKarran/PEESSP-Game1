#ifndef _SCREENBUFFER_H_
#define _SCREENBUFFER_H_

#include <stdint.h>
#include "LCD_HY28B.h"

class ScreenBuffer
{
public:
	ScreenBuffer();
	~ScreenBuffer();

	uint16_t* Buffer();
	void Move_To(uint16_t x, uint16_t y);
	uint16_t X_Pos();
	uint16_t Y_Pos();
	uint16_t Side_Length();
	void Set_Side_Length(uint16_t sideLength);

	void Read_LCD();
	void Render_To_LCD();

private:
	uint16_t xPos; // Screen position of the centre of the buffer.
	uint16_t yPos;
	uint16_t sideLength; // Odd size gives a centre pixel for postion. Always square.
	uint16_t size;
	uint16_t *buffer;
	LCD_HY28B* lcd;

	void Clear();
};

#endif // _SCREENBUFFER_H_
