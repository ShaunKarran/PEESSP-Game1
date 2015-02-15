#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <stdint.h>
#include "LCD_HY28B.h"

#define ADC_RES 12		// bits
#define ADC_SAMPLES 8	// Number of samples per read.

#define VREF	3300 // mV
#define V_DIV	2 	// Battery voltage is divided by 2 otherwise would exceed Vref.
#define V_MAX 	4200 // mV
#define V_MIN	3300 // mV
#define V_RANGE (V_MAX - V_MIN)

class Battery
{
public:
	Battery();
	Battery(uint8_t pin);

	double MilliVoltage();
	uint8_t Percentage();
	void Show_Level(uint16_t xPos, uint16_t yPos);

protected:
	LCD_HY28B* lcd;
	uint8_t pin;
};

#endif // _BATTERY_H_
