// Variables.h

#ifndef _VARIABLES_h
#define _VARIABLES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <hidboot.h>
#include <usbhid.h>
#include "PS3ControllerInterface.h"
#include "TankMotionControl.h"
#include "SerialControllerInterface.h"
#include "WiiControllerInterface.h"
#include "KeyboardControllerInterface.h"



#endif

