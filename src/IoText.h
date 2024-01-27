/**
 * IoText data protocol library for Arduino and PlatformIO embedded platforms
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

using namespace std;

#include <iostream>
#include <variant>
#include <optional>
#include <vector>

#include "types/metric_data_item.h"
#include "types/item_type.h"
#include "types/item.h"
#include "codecs/item_codec.h"
#include "codecs/iot_ext_codec.h"
#include "builders/item_data_builder.h"


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
		string encode_test();
};

#endif /* IOTEXT_H */