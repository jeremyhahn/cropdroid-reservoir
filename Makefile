ORG := jeremyhahn
PACKAGE := harvest.room
TARGET_OS := linux

.PHONY: flash-serial

default: flash-usbasp flash-serial monitor

flash-usbasp:
	avrdude -c usbasp -p m2560 -u -U flash:w:build/Mega/harvest-reservoir.hex
	
flash-serial:
	avrdude -p m2560 -c wiring -P /dev/ttyACM0 -b 115200 -D -U flash:w:build/Mega/harvest-reservoir.hex
	
monitor:
	screen /dev/ttyACM0 115200
