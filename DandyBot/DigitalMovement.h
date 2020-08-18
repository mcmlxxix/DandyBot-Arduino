// DigitalMovement.h

#ifndef _DIGITALMOVEMENT_h
#define _DIGITALMOVEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DigitalMovement
{
public:
	DigitalMovement(int direction);
	int GetDirection();

private:
	int _direction;
};

#endif

