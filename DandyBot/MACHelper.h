#ifndef _MACHELPER_h
#define _MACHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MACHelper
{
public:
	MACHelper();
	uint64_t MAC2Int(const uint8_t hwaddr[]);
	void Int2MAC(const uint64_t mac, uint8_t* hwaddr);
};

#endif
