// MecanumMotor.h

#ifndef _MECANUMMOTOR_h
#define _MECANUMMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MecanumMotor
{
public:
	MecanumMotor(int pwmPin, int forwardPin, int backwardPin);
	void MoveStop(bool forceStop);
	void MoveForward(int speed);
	void MoveBackward(int speed);
private:
	int StandbyPin;
	int PWMPin;
	int ForwardPin;
	int BackwardPin;
	bool movingForward = false;
	bool movingBackward = false;
};

#endif

