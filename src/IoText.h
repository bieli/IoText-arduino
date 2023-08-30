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

class IOText
{
	private:
		long _timestamp = 0;
		char* device_name = "";

	public:

		IOText();

		virtual ~IOText();

		void build(long timestamp, char* device_name);
};

#endif /* IOTEXT_H */