// AnalogMovement.h

#ifndef _ANALOGMOVEMENT_h
#define _ANALOGMOVEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class AnalogMovement
{
	public:
		AnalogMovement(double analogX, double analogY);
		double GetAnalogX();
		double GetAnalogY();

	private:
		double _analogY;
		double _analogX;
};

#endif

