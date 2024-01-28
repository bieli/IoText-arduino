![Platform IO CI](https://github.com/bieli/IoText-arduino/actions/workflows/platformio_ci.yaml/badge.svg)

# IoText-arduino
Arduino IoT library for IoText data protocol. You can build messages with any measuremens to use with MQTT or other data channels.

Library was written in C++ standard 11, because many platforms has limits

## Reference project and full IoText specification

https://github.com/bieli/IoText-data-protocol/


## Builder API
```cpp
#include "IoText.h"
#include "builders/item_data_builder.h"

using namespace std;

IoTextItemDataBuilder builder = IoTextItemDataBuilder(3900237526042, "DEV_NAME_002");
    builder.add_measure(
        "open_door",
        MetricDataItem(
            MetricDataTypes::BOOL,
            MetricValueTypeBuilder()
                .set_bool_value(true)
        )
    )
    .add_measure(
        "open_window",
        MetricDataItem(
            MetricDataTypes::BOOL,
            MetricValueTypeBuilder()
                .set_bool_value(false)
        )
    )
    .add_measure(
        "counter_01",
        MetricDataItem(
            MetricDataTypes::INTEGER,
            MetricValueTypeBuilder()
                .set_integer_value(1234)
        )
    )
    .add_measure(
        "txt_1",
        MetricDataItem(
            MetricDataTypes::TEXT,
            MetricValueTypeBuilder()
                .set_text_value(string("txt"))
        )
    );

string built_msg = builder.build();
String output = built_msg.c_str();

//Expected output:
//t|3900237526042,d|DEV_NAME_002,m|open_door=b:1,m|open_window=b:0,m|counter_01=i:1234,m|txt_1=t:txt
```


## Low-level Item API
```cpp
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

#ifdef ENABLE_DECIMAL_TYPE
  MetricDataItem mdi2 = MetricDataItem(
      MetricDataTypes::DECIMAL,
      MetricValueTypeBuilder()
          .set_decimal_value(1234567890.12345678901234567890)
          .set_decimal_precission(3)
  );
  Item item4 = Item(ItemTypes::METRIC_ITEM, "metric_name", mdi2);
  items.push_back(item4);
#endif

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

  string output = IoTextCodec::encode(items);

```

## Example output from ESP32 terminal - file: examples/IoText_decode_example/IoText_decode_example.ino
```bash
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
ets Jun  8 2016 00:22:57

rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:1344
load:0x40078000,len:13964
load:0x40080400,len:3600
entry 0x400805f0
E (148) psram: PSRAM ID read error: 0xffffffff
Encoded payload:
t|2900267526042,d|devie_id_x3,m|val=t:txt,m|metric_boolean1=b:1,m|metric_integer9=i:3333
---------

Decoded items:

type: t │ name: 2900267526042

type: d │ name: devie_id_x3

type: m │ name: val
        ╘═══ metric -> type: t, value: txt

type: m │ name: metric_boolean1
        ╘═══ metric -> type: b, value: 1

type: m │ name: metric_integer9
        ╘═══ metric -> type: i, value: 3333
TEST FINISHED WITH SUCCESS!
```

## How to develop this library for a few platforms (Linux, Aruino, Esspresif)
```bash
make compile
```


## arduino-cli howto

#### Reinstall library from repo.
```bash
arduino-iotext-lib-reinstall
```

#### Compile
```bash
make compile-arduino-cpp11-encode
make compile-arduino-cpp11-builder
```

## Localhost GCC howto
```bash
make compile-main-cpp11
make compile-main-cpp17
```


## PlatformIO howto

Go to website: https://platformio.org/


### List installed platforms

    platformio platform list


### List available boards

    platformio boards


### Run specific build

    platformio ci --board=esp32dev --lib="." examples//IoText_data_builder_example/


### Run specific environment

    platformio run --environment lopy4


### Build all environments

    platformio run

### "Make clean" for all environments

    platformio run -t clean


### Dump specific build environment

    platformio run --environment lopy4 --target envdump




## TODO
- [x] rewrite C++17 implementation to C++11 standard (platforms limit!!!)
- [x] encoding from string message to data structures
- [x] encoding easy builder
- [x] example Arduino scetches in Arduino library (teady to test library with one click)
- [x] update CI in Github Actions
- [ ] decoding from string message to data structures
- [ ] unit tests
- [ ] unit tests for embedded device (tests runs on hardware)
- [ ] performance, allocated resources stats
- [ ] add critical sections (i.e. mutexes) for FreeRTOS
- [ ] add to official Arduino IDE (1.x and 2.x)
- [ ] run performance and stability tests on different hardwares (for a few weeks on running devices with different speeds devices in MHz)


See slot `CPPDEFINES`.