// MotionController.h

#ifndef _MOTIONCONTROLLER_h
#define _MOTIONCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "AnalogMovement.h"
#include "DigitalMovement.h"

class MotionController
{
public:
	virtual bool Init() { return false; }
	virtual void MoveForward() { };
	virtual void MoveBackward() { };
	virtual void StrafeLeft() { };
	virtual void StrafeRight() { };
	virtual void TurnLeft() { };
	virtual void TurnRight() { };
	virtual void DigitalMove(DigitalMovement movement) { };
	virtual void AnalogMove(AnalogMovement movement) { };
	virtual void MoveStop(bool forceStop) { };

protected:
	bool movingForward = false;
	bool movingBackward = false;
	bool turningLeft = false;
	bool turningRight = false;
	bool strafingLeft = false;
	bool strafingRight = false;
};

#endif

