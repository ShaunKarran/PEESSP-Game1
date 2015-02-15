#ifndef _THUMBSTICK_H_
#define _THUMBSTICK_H_

#include <stdint.h>

#define ADC_RES 12		// bits
#define ADC_SAMPLES 8	// Number of samples per read.

#define DEADZONE_SIZE 85

class Thumbstick
{
public:
	Thumbstick();
	Thumbstick(uint8_t xPin, uint8_t yPin, uint8_t buttonPin);

	void Position(int16_t* x, int16_t* y);
	uint8_t Is_Pressed();

protected:
	int16_t deadZone;
	uint8_t xPin;
	uint8_t yPin;
	uint8_t buttonPin;
};

#endif // _THUMBSTICK_H_
