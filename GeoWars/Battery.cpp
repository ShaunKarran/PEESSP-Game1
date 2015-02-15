#include <WProgram.h>
#include "Battery.h"

Battery::Battery()
{
	this->pin = A3;
	lcd = new LCD_HY28B();
}

Battery::Battery(uint8_t pin)
{
	this->pin = pin;
}

double Battery::MilliVoltage()
{
	uint16_t analogResult = analogRead(pin);
	double voltage = ((analogResult * VREF) / (1 << ADC_RES)); // Scale result to correct voltage.
	return voltage * V_DIV; // Compensate for voltage divider on battery voltage.
}

uint8_t Battery::Percentage()
{
	double voltage = MilliVoltage();
	uint8_t percentage = ((voltage - V_MIN) * 100) / V_RANGE;
	return (percentage < 100) ? percentage : 100;
}

void Battery::Show_Level(uint16_t xPos, uint16_t yPos)
{
	lcd->Draw_Sprite(sprite_battery);
}
