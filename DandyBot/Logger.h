#ifndef _LOGGER_h
#define _LOGGER_h

class Logger
{
public:
	static void Log(String message) {
		Serial.print("\r\n" + message);
	}
	static void Log(char key) {
		Serial.print("\r\n" + key);
	}
};

#endif
