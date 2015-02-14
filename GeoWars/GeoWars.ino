#include <Wprogram.h>
#include <stdint.h>
#include "SPI.h"
#include "LCD_HY28B.h"
#include "ASCII.h"

#include "Game.h"

#define ADC_RES 12		// bits
#define ADC_SAMPLES 8	// Number of samples per read.

int main()
{
	analogReference(EXTERNAL);
	analogReadRes(ADC_RES);
	analogReadAveraging(ADC_SAMPLES);

	randomSeed(analogRead(A0));

	SPI_Init(); // This gets called when the lcd object is created, but leave here anyway.

	Game::Start();

	return 0;
}
