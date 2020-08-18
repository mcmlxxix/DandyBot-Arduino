// ButtonPress.h

#ifndef _BUTTONPRESS_h
#define _BUTTONPRESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ButtonPress
{
public:
	ButtonPress(int button);
	int GetButton();

private:
	int _button;
};


#endif

