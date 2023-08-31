/**
 * IoText data protocol library for Arduino
 * https://github.com/bieli/IoText-arduino
 *
 * Apache 2.0 License
 * (c) 2023 Marcin Bielak
**/

#ifndef IOTEXT_H
#define IOTEXT_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class IoText
{
	private:
		unsigned long timestamp;
		char* device_name;
        char buffer[128];

	public:

		IoText();

		virtual ~IoText();

		char* build(unsigned long timestamp, char* device_name);
};

#endif /* IOTEXT_H */