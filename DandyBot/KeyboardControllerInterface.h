// KeyboardControllerInterface.h

#ifndef _KEYBOARDCONTROLLERINTERFACE_h
#define _KEYBOARDCONTROLLERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <hidboot.h>
#include <usbhub.h>

class KeyboardControllerInterface : public KeyboardReportParser {
public:
    //KeyboardControllerInterface(void (*onKeyDown)(char), void (*onKeyUp)(char));
    //void PrintKey(uint8_t mod, uint8_t key);
    void SetOnKeyDown(void (*onKeyDown)(char*));
    void SetOnKeyUp(void (*onKeyUp)(char*));

protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);
    void OnKeyDown(uint8_t mod, uint8_t key);
    void OnKeyUp(uint8_t mod, uint8_t key);
    //void OnKeyPressed(uint8_t key); 

    /* callbacks */
    void (*KeyDownCallback)(char*);
    void (*KeyUpCallback)(char*);
};

#endif

