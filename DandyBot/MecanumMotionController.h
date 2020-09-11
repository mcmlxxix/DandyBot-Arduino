// MecanumMotionController.h

#ifndef _MECANUMMOTIONCONTROLLER_h
#define _MECANUMMOTIONCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MecanumMotor.h"
#include "MotionController.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"

class MecanumMotionController : public MotionController
{
public:
	bool Init(MecanumMotor *leftForwardMotor, MecanumMotor *rightForwardMotor, MecanumMotor *leftRearMotor, MecanumMotor *rightRearMotor);
	void MoveForward();
	void MoveBackward();
	void TurnLeft();
	void TurnRight();
	void DigitalMove(DigitalMovement movement);
	void AnalogMove(AnalogMovement movement);
	void MoveStop(bool forceStop);

private:
	MecanumMotor* LeftFrontMotor;
	MecanumMotor* RightFrontMotor;
	MecanumMotor* LeftRearMotor;
	MecanumMotor* RightRearMotor;
};

#endif

