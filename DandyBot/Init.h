// Init.h

#ifndef _INIT_h
#define _INIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <usbhub.h>
#include "Logger.h"
#include "Control.h"
#include "PS3ControllerInterface.h"
#include "TankMotionController.h"
#include "SerialControllerInterface.h"
#include "WiiControllerInterface.h"
#include "KeyboardControllerInterface.h"

/* base crap */
USB usb;
BTD bluetoothDongle(&usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> keyboard(&usb);

/* input devices */
PS3ControllerInterface* ps3Controller;
WiiControllerInterface* wiiController;
//SerialControllerInterface* serialController;
KeyboardControllerInterface keyboardController;

/* motion controllers */
TankMotionController tankMotionController;
/* TODO: wheel motion controller */

/* state information */
bool usbInitialized = false;
bool bluetoothInitialized = false;
bool wiiControllerInitialized = false;
bool ps3ControllerInitialized = false;
bool keyboardInitialized = false;
bool tankMotionControllerInitialized = false;

void initSerial() {
    Serial.begin(9600);

#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
}

void onKeyDown(char* key) {
    String cmdString = (String)key;
    DigitalMovement movement(-1);
    bool doMovement = false;

    if (cmdString == "50") { //left
        //Logger::Log("turning left");
        movement = DigitalMovement(LEFT);
        doMovement = true;
    }
    else if (cmdString == "4f") { //right
        //Logger::Log("turning right");
        movement = DigitalMovement(RIGHT);
        doMovement = true;
    }
    else if (cmdString == "52") { //up
        //Logger::Log("moving forward");
        movement = DigitalMovement(UP);
        doMovement = true;
    }
    else if (cmdString == "51") { //down
        //Logger::Log("moving backward");
        movement = DigitalMovement(DOWN);
        doMovement = true;
    }
    else if (cmdString == "29") { //escape
        //Logger::Log("emergency stop");
        movement = DigitalMovement(-1);
        doMovement = true;
    }
    else {
        Logger::Log("unknown command key: " + cmdString);
        return;
    }

    if (tankMotionControllerInitialized && doMovement) {
        tankMotionController.DigitalMove(movement);
    }
    /* TODO: wheel motion controller */
}

void onKeyUp(char* key) {
    //Logger::Log("key released: " + (String) key);
    if (tankMotionControllerInitialized) {
        tankMotionController.MoveStop(false);
    }
    /* TODO: wheel motion controller */
}

bool initUSB() {
    if (usb.Init() == -1) {
        Logger::Log("OSC did not start");
        return false;
    }
    Logger::Log("OSC started");
    return true;
}

bool initBluetooth() {
    //bluetoothDongle = &BTD(&usb);
    if (bluetoothDongle.isReady()) {
        Logger::Log("Bluetooth initialized");
        Logger::Log("Address: " + bluetoothDongle.GetAddress());
        return true;
    }
    Logger::Log("Bluetooth not found");
    return false;
}

bool initWiiController() {
    wiiController = &WiiControllerInterface(&bluetoothDongle);
    if (wiiController->Init()) {
        Logger::Log("Wii controller initialized");
        return true;
    }
    Logger::Log("Wii controller not found");
    return false;
}

bool initPS3Controller() {
    //PS3ControllerInterface ps3Controller(&bluetoothDongle, 0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
    //PS3ControllerInterface ps3Controller(&bluetoothDongle, bluetoothDongle.GetAddress()); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
    ps3Controller = &PS3ControllerInterface(&bluetoothDongle, bluetoothDongle.GetAddress());
    if (ps3Controller->Init()) {
        Logger::Log("PS3 controller initialized");
        return true;
    }
    Logger::Log("PS3 controller not found");
    return false;
}

bool initKeyboard() {
    keyboardController.SetOnKeyDown(&onKeyDown);
    keyboardController.SetOnKeyUp(&onKeyUp);

    if (keyboard.SetReportParser(0, &keyboardController)) {
        Logger::Log("Keyboard initialized");
        return true;
    }
    Logger::Log("Keyboard not found");
    return false;
}

bool initTankMotionController() {
    int lFwdPin = 8;
    int lBckPin = 9;
    int rFwdPin = 11;
    int rBckPin = 10;

    if (tankMotionController.Init(lFwdPin, lBckPin, rFwdPin, rBckPin)) {
        Logger::Log("Tank motion controller initialized");
        return true;
    }
    Logger::Log("Tank motion controller not found");
    return false;
}

#endif

