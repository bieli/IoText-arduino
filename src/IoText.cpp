/**
 * IoText data protocol library for Arduino and PlatformIO embedded platforms
 * https://github.com/bieli/IoText-arduino
 *
 * Apache 2.0 License
 * (c) 2023 Marcin Bielak
**/
#include <Arduino.h>
#include <ArduinoSTL.h>
#include "IoText.h"

#include <iostream>
#include <variant>
#include <optional>
#include <vector>

#include "types/metric_data_item.h"
#include "types/item_type.h"
#include "types/item.h"
#include "codecs/item_codec.h"
#include "codecs/iot_ext_codec.h"


// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wno-volatile"
//<for loop>
// #pragma GCC diagnostic pop

using namespace std;


// TEENSYDUINO has a port of Dean Camera's ATOMIC_BLOCK macros for AVR to ARM Cortex M3.
#define HAS_ATOMIC_BLOCK (defined(ARDUINO_ARCH_AVR) || defined(TEENSYDUINO))

// Whether we are running on either the ESP8266 or the ESP32.
#define ARCH_ESPRESSIF (defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32))

// Whether we are actually running on FreeRTOS.
#define IS_FREE_RTOS defined(ARDUINO_ARCH_ESP32)

// Define macro designating whether we're running on a reasonable
// fast CPU and so should slow down sampling from GPIO.
#define FAST_CPU \
    ( \
    ARCH_ESPRESSIF || \
    defined(ARDUINO_ARCH_SAM)     || defined(ARDUINO_ARCH_SAMD) || \
    defined(ARDUINO_ARCH_STM32)   || defined(TEENSYDUINO) \
    )

#if HAS_ATOMIC_BLOCK
// Acquire AVR-specific ATOMIC_BLOCK(ATOMIC_RESTORESTATE) macro.
#include <util/atomic.h>
#endif

#if FAST_CPU
// Make shiftIn() be aware of clockspeed for
// faster CPUs like ESP32, Teensy 3.x and friends.
// See also:
// - https://github.com/bogde/HX711/issues/75
// - https://github.com/arduino/Arduino/issues/6561
// - https://community.hiveeyes.org/t/using-bogdans-canonical-hx711-library-on-the-esp32/539
uint8_t shiftInSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;

    for(i = 0; i < 8; ++i) {
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(1);
        if(bitOrder == LSBFIRST)
            value |= digitalRead(dataPin) << i;
        else
            value |= digitalRead(dataPin) << (7 - i);
        digitalWrite(clockPin, LOW);
        delayMicroseconds(1);
    }
    return value;
}
#define SHIFTIN_WITH_SPEED_SUPPORT(data,clock,order) shiftInSlow(data,clock,order)
#else
#define SHIFTIN_WITH_SPEED_SUPPORT(data,clock,order) shiftIn(data,clock,order)
#endif

#if ARCH_ESPRESSIF
// ESP8266 doesn't read values between 0x20000 and 0x30000 when DOUT is pulled up.
#define DOUT_MODE INPUT
#else
#define DOUT_MODE INPUT_PULLUP
#endif

IoText::IoText() {
}

IoText::~IoText() {
}

char* IoText::build(unsigned long timestamp, char* device_name) {
    sprintf(buffer, "t|%ld,d|%s", timestamp, device_name);
    return buffer;
}

String IoText::encode_test() {
    vector<Item> items;
    Item item1 = Item(ItemTypes::TIMESTAMP_MILIS, "2900267526042");
    items.push_back(item1);


    Item item2 = Item(ItemTypes::DEVICE_ID, "devie_id_x3");
    items.push_back(item2);

    MetricDataItem mdi = MetricDataItem(
        MetricDataTypes::TEXT,
        MetricValueTypeBuilder()
            .set_text_value(string("txt"))
    );
    Item item3 = Item(ItemTypes::METRIC_ITEM, "val", mdi);
    items.push_back(item3);

    MetricDataItem mdi2 = MetricDataItem(
        MetricDataTypes::DECIMAL,
        MetricValueTypeBuilder()
            .set_decimal_value(1234567890.12345678901234567890)
            .set_decimal_precission(3)
    );
    Item item4 = Item(ItemTypes::METRIC_ITEM, "metric_name", mdi2);
    items.push_back(item4);

    MetricDataItem mdi3 = MetricDataItem(
        MetricDataTypes::BOOL,
        MetricValueTypeBuilder()
            .set_bool_value(true)
    );
    Item item5 = Item(ItemTypes::METRIC_ITEM, "metric_boolean1", mdi3);
    items.push_back(item5);

    MetricDataItem mdi4 = MetricDataItem(
        MetricDataTypes::INTEGER, 
        MetricValueTypeBuilder()
            .set_integer_value(3333)
    );
    Item item6 = Item(ItemTypes::METRIC_ITEM, "metric_integer9", mdi4);
    items.push_back(item6);

    string encoded_payload = IoTextCodec::encode(items);
    cout << "Encoded payload: " << endl << encoded_payload << endl;
    return encoded_payload;
}
