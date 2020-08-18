// WiiControllerInterface.h

#ifndef _WIICONTROLLERINTERFACE_h
#define _WIICONTROLLERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WII.h>
#include "GameControllerInterface.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "ButtonPress.h"

class WiiControllerInterface : public GameControllerInterface {
public:
	WiiControllerInterface(BTD* btd);

	AnalogMovement GetLeftAnalogMovement();
	AnalogMovement GetRightAnalogMovement();
	DigitalMovement GetDigitalMovement();
	ButtonPress GetButtonPress();
	bool Init();
	void Pair();
private:
	BTD* bluetoothDongle;
	WII wiiController;
};

#endif

