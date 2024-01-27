![Platform IO CI](https://github.com/bieli/IoText-arduino/actions/workflows/platformio_ci.yaml/badge.svg)

# IoText-arduino
Arduino IoT library for IoText data protocol. You can build messages with any measuremens to use with MQTT or other data channels.

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
//built_msg: t|3900237526042,d|DEV_NAME_002,m|open_door=b:1,m|open_window=b:0,m|counter_01=i:1234,m|txt_1=t:txt
```

## PlatformIO howto

Go to website: https://platformio.org/


### List installed platforms

    platformio platform list


### List available boards

    platformio boards


### Run specific build

    platformio ci --board=megaatmega2560 --lib="." examples/IoText_decode_example


### Run specific environment

    platformio run --environment lopy4


### Build all environments

    platformio run

### "Make clean" for all environments

    platformio run -t clean


### Dump specific build environment

    platformio run --environment lopy4 --target envdump

See slot `CPPDEFINES`.