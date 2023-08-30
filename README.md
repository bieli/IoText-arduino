![Platform IO CI](https://github.com/bieli/IoText-arduino/actions/workflows/platformio_ci.yml/badge.svg)

# IoText-arduino
Arduino IoT library for IoText data protocol. You can build messages with any measuremens to use with MQTT or other data channels.

## Reference project and full IoText specification





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