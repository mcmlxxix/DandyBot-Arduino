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

/* input devices */
USB usb;
BTD bluetoothDongle(&usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> keyboard(&usb);

/* input interfaces */
PS3ControllerInterface ps3Controller(&bluetoothDongle, bluetoothDongle.GetAddress());
WiiControllerInterface wiiController(&bluetoothDongle);
KeyboardControllerInterface keyboardController;
SerialControllerInterface serialController;

/* motion controllers */
TankMotionController tankMotionController;
/* TODO: wheel motion controller */

/* state information */
bool usbReady = false;
bool bluetoothReady = false;
bool wiiControllerReady = false;
bool ps3ControllerReady = false;
bool keyboardReady = false;
bool tankMotionControllerReady = false;

void processMovementCommand(DigitalMovement movement) {
    if (tankMotionControllerReady) {
        tankMotionController.DigitalMove(movement);
    }
    /* TODO: wheel motion controller */
}

void onSerialData() {
    String cmd = serialController.GetCommand();
    if (cmd != "") {
        DigitalMovement movement(-1);
        bool doMovement = true;
        cmd.toLowerCase();
        if (cmd == "stop" || cmd == "s") {
            //Logger::Log("emergency stop");
            movement = DigitalMovement(-1);
        }
        else if (cmd == "left" || cmd == "l") {
            //Logger::Log("turning left");
            movement = DigitalMovement(LEFT);
        }
        else if (cmd == "right" || cmd == "r") {
            //Logger::Log("turning right");
            movement = DigitalMovement(RIGHT);
        }
        else if (cmd == "fwd" || cmd == "f") {
            //Logger::Log("moving forward");
            movement = DigitalMovement(UP);
        }
        else if (cmd == "back" || cmd == "b") {
            //Logger::Log("moving backward");
            movement = DigitalMovement(DOWN);
        }
        else if (cmd == "help" || cmd == "?") {
            Logger::Log("Commands: stop, left, right, fwd, back, help/?");
            doMovement = false;
        }
        else {
            Logger::Log("Unknown serial command: " + cmd);
            doMovement = false;
        }
        if (doMovement) {
            processMovementCommand(movement);
        }
    }
}

void onKeyDown(char* key) {
    String cmdString = (String)key;
    DigitalMovement movement(-1);
    bool doMovement = true;

    if (cmdString == "50") { //left
        //Logger::Log("turning left");
        movement = DigitalMovement(LEFT);
    }
    else if (cmdString == "4f") { //right
        //Logger::Log("turning right");
        movement = DigitalMovement(RIGHT);
    }
    else if (cmdString == "52") { //up
        //Logger::Log("moving forward");
        movement = DigitalMovement(UP);
    }
    else if (cmdString == "51") { //down
        //Logger::Log("moving backward");
        movement = DigitalMovement(DOWN);
    }
    else if (cmdString == "29") { //escape
        //Logger::Log("emergency stop");
        movement = DigitalMovement(-1);
    }
    else {
        Logger::Log("unknown command key: " + cmdString);
        doMovement = false;
        return;
    }

    if (doMovement) {
        processMovementCommand(movement);
    }
}

void onKeyUp(char* key) {
    //Logger::Log("key released: " + (String) key);
    if (tankMotionControllerReady) {
        tankMotionController.MoveStop(false);
    }
    /* TODO: wheel motion controller */
}

void initSerial() {
    Serial.begin(115200);

#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
}

bool initUSB() {
    if (usb.Init() == -1) {
        Logger::Log("Error initializing OSC");
        return false;
    }
    Logger::Log("OSC ready");
    return true;
}

bool initBluetooth() {
    //int timeout = 5;
    //int counter = 0;
    //while (!bluetoothDongle.isReady() && counter++ < timeout) {
    //    delay(1000);
    //}
    if (bluetoothDongle.isReady()) {
        return true;
    }
    return false;
}

bool initWiiController() {
    if (wiiController.Init()) {
        return true;
    }
    return false;
}

bool initPS3Controller() {
    if (ps3Controller.Init()) {
        return true;
    }
    return false;
}

bool initKeyboard() {
    keyboardController.SetOnKeyDown(&onKeyDown);
    keyboardController.SetOnKeyUp(&onKeyUp);

    if (keyboard.SetReportParser(0, &keyboardController)) {
        Logger::Log("USB keyboard ready");
        return true;
    }
    Logger::Log("Error initializing USB keyboard");
    return false;
}

bool initTankMotionController() {
    int lFwdPin = 8;
    int lBckPin = 9;
    int rFwdPin = 11;
    int rBckPin = 10;

    if (tankMotionController.Init(lFwdPin, lBckPin, rFwdPin, rBckPin)) {
        Logger::Log("Tank motion controller ready");
        return true;
    }
    return false;
}

void scanBluetooth() {
    bool wasReady = bluetoothReady;
    bluetoothReady = initBluetooth();
    if (wasReady && !bluetoothReady) {
        Logger::Log("Bluetooth disconnected");
    }
    else if (!wasReady && bluetoothReady) {
        Logger::Log("Bluetooth ready");
    }
}

void scanPeripherals() {
    bool wasWiiReady = wiiControllerReady;
    bool wasPS3Ready = ps3ControllerReady;
    if (bluetoothReady) {
        wiiControllerReady = initWiiController();
        ps3ControllerReady = initPS3Controller();
    }
    else {
        wiiControllerReady = false;
        ps3ControllerReady = false;
    }
    if (wasWiiReady && !wiiControllerReady) {
        Logger::Log("Wiimote disconnected");
    }
    else if (!wasWiiReady && wiiControllerReady) {
        Logger::Log("Wiimote connected");
    }
    if (wasPS3Ready && !ps3ControllerReady) {
        Logger::Log("PS3 controller disconnected");
    }
    else if (!wasPS3Ready && ps3ControllerReady) {
        Logger::Log("PS3 controller connected");
    }
}

void scanControllerInput() {
    /* get manual directional movement from game controller input sources */
    if (wiiControllerReady) {
        DigitalMovement movement = getControllerMovement(&wiiController);
        processMovementCommand(movement);
    }
    else if (ps3ControllerReady) {
        DigitalMovement movement = getControllerMovement(&ps3Controller);
        processMovementCommand(movement);
    }
}
#endif

