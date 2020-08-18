// PS3ControllerInterface.h

#ifndef _PS3CONTROLLERINTERFACE_h
#define _PS3CONTROLLERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <PS3BT.h>
#include "GameControllerInterface.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "ButtonPress.h"
#include "MACHelper.h"

class PS3ControllerInterface : public GameControllerInterface {
public:
	//PS3BT PS3(&Btd, 0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
	PS3ControllerInterface(BTD* btd, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6);
	PS3ControllerInterface(BTD* btd, uint8_t macAddress);

	AnalogMovement GetLeftAnalogMovement();
	AnalogMovement GetRightAnalogMovement();
	DigitalMovement GetDigitalMovement();
	ButtonPress GetButtonPress();
	bool Init();
private:
	BTD* bluetoothDongle;
	PS3BT ps3Controller;
	MACHelper macHelper;
};

#endif

