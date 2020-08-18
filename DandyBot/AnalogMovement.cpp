// Analog movement class for arduino board
// 
// 

#include "AnalogMovement.h"

AnalogMovement::AnalogMovement(double analogX, double analogY)
{
	_analogX = analogX;
	_analogY = analogY;
}

double AnalogMovement::GetAnalogX() {
	return _analogX;
}

double AnalogMovement::GetAnalogY() {
	return _analogY;
}
