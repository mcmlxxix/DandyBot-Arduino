/*
 Name:		DandyBot.ino
 Created:	8/16/2020 12:52:16 PM
 Author:	mcmlxxix
*/

#include <XBOXUSB.h>
#include <XBOXONE.h>
#include <XBOXRECV.h>
#include <xboxEnums.h>
#include <XBOXOLD.h>
#include <version_helper.h>
#include <Wii.h>
#include <Usb.h>
#include <SPP.h>
#include <settings.h>
#include <PSBuzz.h>
#include <PS4USB.h>
#include <PS4Parser.h>
#include <PS3USB.h>
#include <PS4BT.h>
#include <PS3Enums.h>
#include <PS3BT.h>
#include <max_LCD.h>
#include <masstorage.h>
#include <hiduniversal.h>
#include <hidusagestr.h>
#include <hidescriptorparser.h>
#include <hidcomposite.h>
#include <hidboot.h>
#include <controllerEnums.h>
#include <BTHID.h>
#include <cdcacm.h>
#include <BTD.h>
#include <adk.h>
#include "Logger.h"
#include "Init.h"
#include "Control.h"

int loopCount = 0;
int loopDelayMS = 10;
int bluetoothRescanMS = 5000;
int peripheralRescanMS = 1000;

void errorLoop() {
    while (1) {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }
}

void setup() {
    Logger::Log("\r\n######### BEGIN ###########\r\n");

    initSerial();

    usbReady = initUSB();
    tankMotionControllerReady = initTankMotionController();
    mecanumMotionControllerReady = initMecanumMotionController();

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


