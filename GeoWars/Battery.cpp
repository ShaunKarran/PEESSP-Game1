#include <WProgram.h>
#include "Battery.h"

Battery::Battery()
{
	this->pin = A3;
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
	return ((voltage - V_MIN) * 100) / V_RANGE;
}
