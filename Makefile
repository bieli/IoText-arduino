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

compile1:
	g++ -std=gnu++17 -fno-exceptions -fpermissive -fexceptions -Isrc/types -Isrc/codecs src/main.cc -o main

compile2:
	g++ -std=c++17 src/main2.cc -o main2

clean:
	$(platformio) run -t clean
