all: flash

build/main.hex: main.c
	sdcc main.c -o build/main.hex

flash: build/main.hex
	stcgal -P stc89 -p /dev/ttyCH341USB0 -a build/main.hex
