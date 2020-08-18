// 
// 
// 

#include "SerialControllerInterface.h"

SerialControllerInterface::SerialControllerInterface() {
	buffer = "";
}

String SerialControllerInterface::GetCommand() {
	if (Serial.available() > 0) {
		char received = Serial.read();
		if (received == '\n')
		{
			String command = buffer.substring(0);
			Serial.print("\r\nreceived serial command: " + command);
			buffer = "";
			return command;
		}
		else {
			buffer += received;
		}
	}
	return "";
}
