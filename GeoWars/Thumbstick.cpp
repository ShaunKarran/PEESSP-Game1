#include <WProgram.h>
#include "Thumbstick.h"
#include "Helpers.h"

Thumbstick::Thumbstick()
{
	this->deadZone = DEADZONE_SIZE; // Arbitrary number for now.
	this->xPin = A8;
	this->yPin = A7;
	this->buttonPin = 23;
	pinMode(buttonPin, INPUT);
}

Thumbstick::Thumbstick(uint8_t xPin, uint8_t yPin, uint8_t buttonPin)
{
	this->deadZone = DEADZONE_SIZE; // Arbitrary number for now.
	this->xPin = xPin;
	this->yPin = yPin;
	this->buttonPin = buttonPin;
	pinMode(buttonPin, INPUT);
}

void Thumbstick::Position(int16_t* x, int16_t* y)
{
	int16_t tempX = analogRead(xPin);
	int16_t tempY = analogRead(yPin);
	tempX -= (1 << (ADC_RES - 1)); // Adjust the value to centre on 0.
	tempY -= (1 << (ADC_RES - 1));

    // Ensure the magnitude of the direction vector doesnt exceed the magnitude of an individual axis.
    double vect[2] = { tempX, tempY };
    double vectMag = Mag(vect, 2);
    if (vectMag > (1 << (ADC_RES - 1)))
    {
        tempX = tempX / vectMag * (1 << ADC_RES - 1);
        tempY = tempY / vectMag * (1 << ADC_RES - 1);
    }

    *x = (abs(tempX) > deadZone) ? tempX : 0; // Check value is > deadZone.
    *y = (abs(tempY) > deadZone) ? tempY : 0;
}

uint8_t Thumbstick::Is_Pressed()
{
	uint16_t pressedConfidence = 0;
    uint16_t releasedConfidence = 0;

    while (1)
    {
        if (digitalRead(buttonPin))
        {
            pressedConfidence++;
            releasedConfidence = 0;
            if (pressedConfidence > 300)
            {
                return 1;
            }
        }
        else
        {
            releasedConfidence++;
            pressedConfidence = 0;
            if (releasedConfidence > 300)
            {
                return 0;
            }
        }
    }
}
