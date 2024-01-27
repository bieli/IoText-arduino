# ============
# Main targets
# ============


# -------------
# Configuration
# -------------

$(eval venvpath     := .venv)
$(eval pip          := $(venvpath)/bin/pip)
$(eval python       := $(venvpath)/bin/python)
$(eval platformio   := $(venvpath)/bin/platformio)

# Setup Python virtualenv
setup-virtualenv:
	@test -e $(python) || `command -v virtualenv` --python=python3 $(venvpath)

# CFLAGS = -std=gnu++11 -fno-exceptions -fpermissive -fexceptions -Isrc/types -Isrc/codecs

# ----------
# PlatformIO
# ----------

install-platformio: setup-virtualenv
	@$(pip) install platformio --quiet

build-all: install-platformio
	@$(platformio) run

build-env: install-platformio
	@$(platformio) run --environment $(environment)


# Note: This are legacy build targets, the new ones are defined through `platformio.ini`.

ci-all: install-platformio
	# atmelavr
	$(platformio) ci --board=megaatmega2560 --lib="." examples/IoText_decode_example
	$(platformio) ci --board=megaatmega2560 --lib="." examples/IoText_encode_example

	# atmelavr
	$(MAKE) ci-basic board=feather328p

	# espressif8266
	$(MAKE) ci-basic board=huzzah

	# espressif32
	$(MAKE) ci-basic board=lopy4

	# atmelsam
	$(MAKE) ci-basic board=adafruit_feather_m0
	$(MAKE) ci-basic board=adafruit_feather_m4

	# bluepill
	$(MAKE) ci-basic board=bluepill_f103c8

ci-basic:
	$(platformio) ci --board=$(board) --lib="." examples/IoText_decode_example --verbose
	$(platformio) ci --board=$(board) --lib="." examples/IoText_encode_example --verbose


install-pio-deps:
	$(platformio) pkg install -e bluepill
	$(platformio) pkg install -e esp32dev

compile-main-cpp03:
	g++ -std=c++03 -Lsrc/ main.cc -o ./main_cpp03 && ./main_cpp03

compile-main-cpp11:
	g++ -std=c++11 -Lsrc/ main.cc -o ./main_cpp11 && ./main_cpp11

compile-main-cpp17:
	g++ -std=c++17 -Lsrc/ main.cc -o ./main_cpp17 && ./main_cpp17

compile-pio-esp32-cpp11-encode:
	platformio ci --board=esp32dev --lib="." examples/IoText_encode_example

compile-pio-esp32-cpp11-decode:
	platformio ci --board=esp32dev --lib="." examples/IoText_decode_example

compile-pio-esp32-cpp11-builder:
	platformio ci --board=esp32dev --lib="." examples//IoText_data_builder_example

compile-arduino-esp32-cpp11-encode:
	/tmp/arduino-cli compile -b esp32:esp32:esp32 `pwd`/examples/IoText_encode_example

compile-arduino-esp32-cpp11-decode:
	/tmp/arduino-cli compile -b esp32:esp32:esp32 `pwd`/examples/IoText_decode_example

compile-arduino-esp32-cpp11-builder:
	/tmp/arduino-cli compile -b esp32:esp32:esp32 `pwd`/examples/IoText_data_builder_example

compile1:
	g++ -std=gnu++17 -fno-exceptions -fpermissive -fexceptions -Isrc/types -Isrc/codecs main.cc -Isrc/builders -o main1_main_cpp17

compile2:
	g++ -std=c++17 main2.cpp -o main2_cpp17

arduino-iotext-lib-reinstall:
	/tmp/arduino-cli lib uninstall 'IoText data protocol Arduino Library'
	/tmp/arduino-cli --config-file arduino-cli.yaml lib install --git-url https://github.com/bieli/IoText-arduino#main
	/tmp/arduino-cli lib list

clean:
	$(platformio) run -t clean

compile:
	make compile-main-cpp11
	make compile-main-cpp17
	make compile-pio-esp32-cpp11-encode
	make compile-arduino-esp32-cpp11-encode
	make compile-pio-esp32-cpp11-decode
	make compile-arduino-esp32-cpp11-decode
	make compile-pio-esp32-cpp11-builder
	make compile-arduino-esp32-cpp11-builder

#$ cat > arduino-cli.yaml
#library:
#  enable_unsafe_install: true
#^Z
#/tmp/arduino-cli --config-file arduino-cli.yaml lib install --git-url https://github.com/bieli/IoText-arduino#main
#--git-url and --zip-path flags allow installing untrusted files, use it at your own risk.
#Enumerating objects: 147, done.
#Counting objects: 100% (147/147), done.
#Compressing objects: 100% (105/105), done.
#Total 147 (delta 65), reused 113 (delta 39), pack-reused 0
#Library installed

#/tmp/arduino-cli lib install ArduinoSTL

#/tmp/arduino-cli lib list
#Name                                 Zainstalowany  Dostępne Location              Description
#ArduinoSTL                           1.3.3         -        LIBRARY_LOCATION_USER -
#IoText data protocol Arduino Library 0.1.0          -        LIBRARY_LOCATION_USER -


# /tmp/arduino-cli lib install --git-url https://github.com/bieli/IoText-arduino#main
# /tmp/arduino-cli compile -b esp32:esp32:esp32 `pwd`/examples/IoText_encode_example/

