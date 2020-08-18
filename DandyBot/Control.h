// Control.h

#ifndef _CONTROL_h
#define _CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DigitalMovement.h"
#include "GameControllerInterface.h"

/* process direction pad input from various input sources */
DigitalMovement getControllerMovement(GameControllerInterface* controller) {
    DigitalMovement movement(-1);
    if (movement.GetDirection() == -1) {
        movement = controller->GetDigitalMovement();
        if (movement.GetDirection() != -1) {
            //Logger::Log("Movement direction: " + movement.GetDirection());
        }
    }
    return movement;
}

#endif

