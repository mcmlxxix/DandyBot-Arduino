// Wii Controller Interface
// 
// 

#include <Wii.h>
#include "WiiControllerInterface.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "ButtonPress.h"

WiiControllerInterface::WiiControllerInterface(BTD* btd)
	: bluetoothDongle(btd), wiiController(btd)
{
	//0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13
	analogMin = 0;
	analogMax = 360;
	analogNeutalLow = 170;
	analogNeutralHigh = 190;
}

bool WiiControllerInterface::Init() {
	bool connected = wiiController.wiimoteConnected;
	if (connected) {
		wiiController.setAllOff();
		wiiController.setLedOn(LED1);
	}
	return connected;
}

void WiiControllerInterface::Pair() {
	//wiiController.pair();
}

AnalogMovement WiiControllerInterface::GetLeftAnalogMovement()
{
	if (wiiController.wiiUProControllerConnected) {
		uint16_t leftHatX = wiiController.getAnalogHat(LeftHatX);
		uint16_t leftHatY = wiiController.getAnalogHat(LeftHatY);
		if (leftHatX > analogNeutralHigh || leftHatX < analogNeutalLow || leftHatY > analogNeutralHigh || leftHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(leftHatX), GetPowerRatio(leftHatY));
		}
	}
	else if (wiiController.wiimoteConnected) {
		uint16_t leftHatX = wiiController.getWiimoteRoll();
		uint16_t leftHatY = wiiController.getWiimotePitch();
		if (leftHatX > analogNeutralHigh || leftHatX < analogNeutalLow || leftHatY > analogNeutralHigh || leftHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(leftHatX), GetPowerRatio(leftHatY));
		}
	}
	return AnalogMovement(0, 0);
}

AnalogMovement WiiControllerInterface::GetRightAnalogMovement()
{
	if (wiiController.wiiUProControllerConnected) {
		uint16_t rightHatX = wiiController.getAnalogHat(RightHatX);
		uint16_t rightHatY = wiiController.getAnalogHat(RightHatY);
		if (rightHatX > analogNeutralHigh || rightHatX < analogNeutalLow || rightHatY > analogNeutralHigh || rightHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(rightHatX), GetPowerRatio(rightHatY));
		}
	}
	else if (wiiController.nunchuckConnected) {
		uint16_t rightHatX = wiiController.getNunchuckRoll();
		uint16_t rightHatY = wiiController.getNunchuckPitch();
		if (rightHatX > analogNeutralHigh || rightHatX < analogNeutalLow || rightHatY > analogNeutralHigh || rightHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(rightHatX), GetPowerRatio(rightHatY));
		}
	}

	return AnalogMovement(0, 0);
}

DigitalMovement WiiControllerInterface::GetDigitalMovement() {
	if (wiiController.wiimoteConnected || wiiController.wiiUProControllerConnected) {
		if (wiiController.getButtonPress(UP)) {
			return DigitalMovement(UP);
		}
		else if (wiiController.getButtonPress(RIGHT)) {
			return DigitalMovement(RIGHT);
		}
		else if (wiiController.getButtonPress(DOWN)) {
			return DigitalMovement(DOWN);
		}
		else if (wiiController.getButtonPress(LEFT)) {
			return DigitalMovement(LEFT);
		}
	}
	return DigitalMovement(-1);
}

ButtonPress WiiControllerInterface::GetButtonPress() {
	if (wiiController.wiimoteConnected || wiiController.wiiUProControllerConnected) {
		if (wiiController.getButtonClick(HOME))
			return ButtonPress(HOME);
		if (wiiController.getButtonClick(PLUS))
			return ButtonPress(PLUS);
		if (wiiController.getButtonClick(MINUS))
			return ButtonPress(MINUS);
		if (wiiController.getButtonClick(ONE))
			return ButtonPress(ONE);
		if (wiiController.getButtonClick(TWO))
			return ButtonPress(TWO);
		if (wiiController.getButtonClick(A))
			return ButtonPress(A);
		if (wiiController.getButtonClick(B))
			return ButtonPress(B);

		if (wiiController.wiiUProControllerConnected) {
			if (wiiController.getButtonClick(L))
				return ButtonPress(L);
			if (wiiController.getButtonClick(R))
				return ButtonPress(R);
			if (wiiController.getButtonClick(ZL))
				return ButtonPress(ZL);
			if (wiiController.getButtonClick(ZR))
				return ButtonPress(ZR);
		}
	}
	return ButtonPress(-1);
}
