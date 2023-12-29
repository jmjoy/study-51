.PHONY: all build flash

all: flash

build: build/main.hex

build/main.hex: main.c
	sdcc main.c -o build/main.hex

flash: build
	stcgal -P auto -p /dev/ttyCH341USB0 -a build/main.hex
