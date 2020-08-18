/*
 Name:		DandyBot.ino
 Created:	8/16/2020 12:52:16 PM
 Author:	mcmlxxix
*/

#include "Logger.h"
#include "Init.h"
#include "Control.h"

void setup() {
    Logger::Log("\r\n");

    initSerial();

    usbInitialized = initUSB();
    tankMotionControllerInitialized = initTankMotionController();

    if (usbInitialized) {
        keyboardInitialized = initKeyboard();
        bluetoothInitialized = initBluetooth();
        if (bluetoothInitialized) {
            wiiControllerInitialized = initWiiController();
            ps3ControllerInitialized = initPS3Controller();
        }
    }

    Logger::Log("\r\n");
}

void loop() {

    if (!usbInitialized) {
        errorLoop();
    }
    else {
        usb.Task();
    }

    /* get manual directional movement from game controller input sources */
    if (wiiControllerInitialized) {
        DigitalMovement movement = getControllerMovement(wiiController);
        tankMotionController.DigitalMove(movement);
    }
    else if (ps3ControllerInitialized) {
        DigitalMovement movement = getControllerMovement(ps3Controller);
        tankMotionController.DigitalMove(movement);
    }

    delay(100);
}

/* get serial commands (BROKEN) */
void serialEvent() {
    //String cmd = serialController.GetCommand();
    //if (cmd != "") {
    //    cmd.toLowerCase();
    //    if (cmd == "stop") {
    //        tankMotionController.MoveStop(true);
    //    }
    //    else if (cmd == "left") {
    //        tankMotionController.TurnLeft();
    //    }
    //    else if (cmd == "right") {
    //        tankMotionController.TurnRight();
    //    }
    //    else if (cmd == "fwd") {
    //        tankMotionController.MoveForward();
    //    }
    //    else if (cmd == "back") {
    //        tankMotionController.MoveBackward();
    //    }
    //}
}

void errorLoop() {
    while (1) {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
    }
}

