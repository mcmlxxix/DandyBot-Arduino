// Playstation 3 bluetooth controller interface
// 
// 

#include "PS3ControllerInterface.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "ButtonPress.h"
#include "MACHelper.h"

PS3ControllerInterface::PS3ControllerInterface(BTD *btd, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6)
	: bluetoothDongle(btd), ps3Controller(btd, a1, a2, a3, a4, a5, a6), macHelper()
{
	//0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13
}

PS3ControllerInterface::PS3ControllerInterface(BTD* btd, uint8_t macAddress)
	: bluetoothDongle(btd), ps3Controller(btd, macAddress)
{
	//0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13
}

bool PS3ControllerInterface::Init() {
	analogMin = 0;
	analogMax = 255;
	analogNeutalLow = 117;
	analogNeutralHigh = 137;
	return ps3Controller.PS3Connected;
}

AnalogMovement PS3ControllerInterface::GetLeftAnalogMovement()
{
	if (ps3Controller.PS3Connected || ps3Controller.PS3NavigationConnected) {
		uint16_t leftHatX = ps3Controller.getAnalogHat(LeftHatX);
		uint16_t leftHatY = ps3Controller.getAnalogHat(LeftHatY);
		if (leftHatX > analogNeutralHigh || leftHatX < analogNeutalLow || leftHatY > analogNeutralHigh || leftHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(leftHatX), GetPowerRatio(leftHatY));
		}
	}
	return AnalogMovement(0, 0);
}

AnalogMovement PS3ControllerInterface::GetRightAnalogMovement()
{
	if (ps3Controller.PS3Connected || ps3Controller.PS3NavigationConnected) {
		uint16_t rightHatX = ps3Controller.getAnalogHat(RightHatX);
		uint16_t rightHatY = ps3Controller.getAnalogHat(RightHatY);
		if (rightHatX > analogNeutralHigh || rightHatX < analogNeutalLow || rightHatY > analogNeutralHigh || rightHatY < analogNeutalLow) {
			return AnalogMovement(GetPowerRatio(rightHatX), GetPowerRatio(rightHatY));
		}
	}
	return AnalogMovement(0, 0);
}

DigitalMovement PS3ControllerInterface::GetDigitalMovement() {
	if (ps3Controller.PS3Connected || ps3Controller.PS3NavigationConnected) {
		if (ps3Controller.getButtonPress(UP)) {
			return DigitalMovement(UP);
		}
		else if (ps3Controller.getButtonPress(RIGHT)) {
			return DigitalMovement(RIGHT);
		}
		else if (ps3Controller.getButtonPress(DOWN)) {
			return DigitalMovement(DOWN);
		}
		else if (ps3Controller.getButtonPress(LEFT)) {
			return DigitalMovement(LEFT);
		}
	}
	return DigitalMovement(-1);
}

ButtonPress PS3ControllerInterface::GetButtonPress() {
	if (ps3Controller.PS3Connected || ps3Controller.PS3NavigationConnected) {
		/* L2 and R2 are analog - treat as digital */
		if (ps3Controller.getAnalogButton(L2) > 10) {
			return ButtonPress(L2);
		}
		if (ps3Controller.getAnalogButton(R2) > 10) {
			return ButtonPress(R2);
		}
		if (ps3Controller.getButtonClick(PS))
			return ButtonPress(PS);
		if (ps3Controller.getButtonClick(TRIANGLE))
			return ButtonPress(TRIANGLE);
		if (ps3Controller.getButtonClick(CIRCLE))
			return ButtonPress(CIRCLE);
		if (ps3Controller.getButtonClick(CROSS))
			return ButtonPress(CROSS);
		if (ps3Controller.getButtonClick(SQUARE))
			return ButtonPress(SQUARE);
		if (ps3Controller.getButtonClick(L1))
			return ButtonPress(L1);
		if (ps3Controller.getButtonClick(L3))
			return ButtonPress(L3);
		if (ps3Controller.getButtonClick(R1))
			return ButtonPress(R1);
		if (ps3Controller.getButtonClick(R3))
			return ButtonPress(R3);
		if (ps3Controller.getButtonClick(SELECT))
			return ButtonPress(SELECT);
		if (ps3Controller.getButtonClick(START))
			return ButtonPress(START);
	}
	return ButtonPress(-1);
}
