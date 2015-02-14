#include "Distance.h"
#include <math.h>

uint16_t Distance_2D(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
