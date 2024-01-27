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

## Example output from ESP32 terminal
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
E (151) psram: PSRAM ID read error: 0xffffffff
IoText build string:t|2900267526042,d|devie_id_x3,m|val=t:txt,m|metric_boolean1=b:1,m|metric_integer9=i:3333
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