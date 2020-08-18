// TankMotionController.h

#ifndef _TANKMOTIONCONTROLLER_h
#define _TANKMOTIONCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MotionController.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"

class TankMotionController : public MotionController
{
public:
	bool Init(int leftForwardPin, int leftBackwardPin, int rightForwardPin, int rightBackwardPin);
	void MoveForward();
	void MoveBackward();
	void TurnLeft();
	void TurnRight();
	void DigitalMove(DigitalMovement movement);
	void AnalogMove(AnalogMovement movement);
	void MoveStop(bool forceStop);

private:
	int LeftForwardPin;
	int LeftBackwardPin;
	int RightForwardPin;
	int RightBackwardPin;
};

#endif

