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
		long timestamp;
		char* device_name;

	public:

		IoText();

		virtual ~IoText();

		void build(long timestamp, char* device_name);
};

#endif /* IOTEXT_H */