
.PHONY: clean flash-usbasp flash-serial monitor

default: flash-serial monitor

clean:
	rm -rf build/

download:
	avrdude -pm328p -cusbasp -u -U flash:r:flash.hex:i # save flash as "flash.hex", in Intel format

flash-usbasp:
	avrdude -c usbasp -p m2560 -u -U flash:w:build/Mega/cropdroid-reservoir.hex
	
flash-serial:
	avrdude -p m2560 -c wiring -P /dev/ttyACM0 -b 115200 -D -U flash:w:build/Mega/cropdroid-reservoir.hex
	
monitor:
	screen /dev/ttyACM0 115200
