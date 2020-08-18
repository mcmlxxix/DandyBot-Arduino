// ControllerInterface.h

#ifndef _CONTROLLERINTERFACE_h
#define _CONTROLLERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <BTD.h>
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "ButtonPress.h"

class ControllerInterface {
public:
	ControllerInterface() {	};

	virtual AnalogMovement GetLeftAnalogMovement() {
		return AnalogMovement(0, 0);
	};
	virtual AnalogMovement GetRightAnalogMovement() {
		return AnalogMovement(0, 0);
	};
	virtual DigitalMovement GetDigitalMovement() {
		return DigitalMovement(-1);
	};
	virtual ButtonPress GetButtonPress() {
		return ButtonPress(-1);
	};
	virtual bool Init() {
		return false;
	}
protected:
	virtual double GetPowerRatio(int analogValue) {
		return (((analogMax / 2) - analogValue) / (analogMax / 2));
	};
	BTD* bluetoothDongle;
	int analogMin;
	int analogMax;
	int analogNeutalLow;
	int analogNeutralHigh;
};

#endif

