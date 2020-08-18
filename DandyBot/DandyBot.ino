/*
 Name:		DandyBot.ino
 Created:	8/16/2020 12:52:16 PM
 Author:	mcmlxxix
*/

#include "Logger.h"
#include "Init.h"
#include "Control.h"

int loopCount = 0;
int loopDelayMS = 10;
int bluetoothRescanMS = 5000;
int peripheralRescanMS = 1000;

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
    bool bluetoothRescan = (++loopCount * loopDelayMS) % bluetoothRescanMS == 0;
    if (bluetoothRescan) {
        //Logger::Log("Scanning bluetooth");
        scanBluetooth();
        //loopCount = 0;
    }

    bool peripheralRescan = (loopCount * loopDelayMS) % peripheralRescanMS == 0;
    if (bluetoothReady && peripheralRescan) {
        //Logger::Log("Scanning peripherals");
        scanPeripherals();
        //loopCount = 0;
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


