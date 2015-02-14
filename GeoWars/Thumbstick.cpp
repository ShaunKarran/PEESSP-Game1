#include <WProgram.h>
#include "Thumbstick.h"

Thumbstick::Thumbstick()
{
	this->deadZone = 150; // Arbitrary number for now.
	this->xPin = A8;
	this->yPin = A7;
	this->buttonPin = 23;
	pinMode(buttonPin, INPUT);
}

Thumbstick::Thumbstick(uint8_t xPin, uint8_t yPin, uint8_t buttonPin)
{
	this->deadZone = 150; // Arbitrary number for now.
	this->xPin = xPin;
	this->yPin = yPin;
	this->buttonPin = buttonPin;
	pinMode(buttonPin, INPUT);
}

void Thumbstick::Position(int16_t* x, int16_t* y)
{
	int16_t tempX = analogRead(xPin);
	int16_t tempY = analogRead(yPin);
	tempX -= (1 << (ADC_RES - 1)); // Adjust the value to centre on 0. 12 bit resolution.
	tempY -= (1 << (ADC_RES - 1));
	*x = (abs(tempX) > deadZone) ? tempX : 0; // Check value is > deadZone.
	*y = (abs(tempY) > deadZone) ? tempY : 0;
}

void Thumbstick::Set_Dead_Zone(uint16_t deadZone)
{
	this->deadZone = deadZone;
}

uint16_t Thumbstick::Dead_Zone()
{
	return deadZone;
}

uint8_t Thumbstick::Is_Pressed()
{
	uint32_t pressedConfidence = 0;
    uint32_t releasedConfidence = 0;

    while (1) {
        if (digitalRead(buttonPin)) {
            pressedConfidence++;
            releasedConfidence = 0;
            if (pressedConfidence > 40000) {
                pressedConfidence = 0;
                return 1;
            }
        } else {
            releasedConfidence++;
            pressedConfidence = 0;
            if (releasedConfidence > 40000) {
                releasedConfidence = 0;
                return 0;
            }
        }
    }
}
