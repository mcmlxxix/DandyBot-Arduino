/*
 Name:		DandyBot.ino
 Created:	8/16/2020 12:52:16 PM
 Author:	mcmlxxix
*/

#include "Logger.h"
#include "Init.h"
#include "Control.h"

int loopCount = 0;
int loopDelayMS = 100;
int bluetoothRescanMS = 5000;

void setup() {
    Logger::Log("\r\n######### BEGIN ###########\r\n");

    initSerial();

    usbReady = initUSB();
    tankMotionControllerReady = initTankMotionController();

    if (usbReady) {
        keyboardReady = initKeyboard();
    }
}

void loop() {

    if (!usbReady) {
        errorLoop();
    }
    else {
        usb.Task();
    }

    /* retry bluetooth init every n milliseconds */
    bool rescan = (++loopCount * loopDelayMS) % bluetoothRescanMS == 0;
    if (rescan) {
        scanBluetooth();
        scanPeripherals();
        loopCount = 0;
    }

    /* check connected controllers for input */
    if (bluetoothReady && (wiiControllerReady || ps3ControllerReady)) {
        scanControllerInput();
    }

    delay(loopDelayMS);
}

/* get serial commands (BROKEN) */
void serialEvent() {
    onSerialData();
}

void errorLoop() {
    while (1) {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }
}


