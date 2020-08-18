// SerialControllerInterface.h

#ifndef _SERIALCONTROLLERINTERFACE_h
#define _SERIALCONTROLLERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SerialControllerInterface {
public:
	SerialControllerInterface();
	String GetCommand();
private:
	String buffer;
};

#endif

