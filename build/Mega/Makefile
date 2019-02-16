ifeq ($(OS),Windows_NT)
SHELL = cmd
RMDIR = rmdir /s /q
RM = del /q
mymkdir = if not exist "$1" mkdir "$1"
else
RMDIR = rm -fr
RM = rm -f
mymkdir = mkdir -p $1
endif

PROJECT_OBJS = \
	project/main.cpp.o \

PLATFORM_CORE_OBJS = \
	core/wiring_digital.c.o \
	core/WString.cpp.o \
	core/CDC.cpp.o \
	core/Tone.cpp.o \
	core/wiring_shift.c.o \
	core/HardwareSerial2.cpp.o \
	core/USBCore.cpp.o \
	core/HardwareSerial1.cpp.o \
	core/IPAddress.cpp.o \
	core/WInterrupts.c.o \
	core/wiring.c.o \
	core/wiring_pulse.S.o \
	core/HardwareSerial.cpp.o \
	core/wiring_analog.c.o \
	core/hooks.c.o \
	core/main.cpp.o \
	core/PluggableUSB.cpp.o \
	core/HardwareSerial0.cpp.o \
	core/Stream.cpp.o \
	core/new.cpp.o \
	core/WMath.cpp.o \
	core/HardwareSerial3.cpp.o \
	core/Print.cpp.o \
	core/abi.cpp.o \
	core/wiring_pulse.c.o \

PLATFORM_VARIANT_OBJS = \

LIBRARIES_OBJS = \
	libraries/Wire/src/Wire.cpp.o \
	libraries/Wire/src/utility/twi.c.o \
	libraries/DallasTemperature/3.8.0/DallasTemperature.cpp.o \
	libraries/SPI/src/SPI.cpp.o \
	libraries/OneWire/2.3.4/OneWire.cpp.o \
	libraries/DHT_sensor_library/1.3.2/DHT.cpp.o \
	libraries/DHT_sensor_library/1.3.2/DHT_U.cpp.o \
	libraries/Ethernet/2.0.0/src/EthernetUdp.cpp.o \
	libraries/Ethernet/2.0.0/src/EthernetServer.cpp.o \
	libraries/Ethernet/2.0.0/src/socket.cpp.o \
	libraries/Ethernet/2.0.0/src/Ethernet.cpp.o \
	libraries/Ethernet/2.0.0/src/Dns.cpp.o \
	libraries/Ethernet/2.0.0/src/Dhcp.cpp.o \
	libraries/Ethernet/2.0.0/src/utility/w5100.cpp.o \
	libraries/Ethernet/2.0.0/src/EthernetClient.cpp.o \

TARGETS = \
	harvest-reservoir.hex \
	harvest-reservoir.eep \

all: $(TARGETS)

harvest-reservoir.hex: harvest-reservoir.elf
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-objcopy" -O ihex -R .eeprom  "./harvest-reservoir.elf" "./harvest-reservoir.hex"

harvest-reservoir.eep: harvest-reservoir.elf
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "./harvest-reservoir.elf" "./harvest-reservoir.eep"

harvest-reservoir.elf: $(PROJECT_OBJS) $(LIBRARIES_OBJS) core.a
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega2560  -o "./harvest-reservoir.elf" $(PROJECT_OBJS) $(LIBRARIES_OBJS) "./core.a" "-L." -lm

core.a:	$(PLATFORM_CORE_OBJS) $(PLATFORM_VARIANT_OBJS)

clean:
	-$(RMDIR) project core variant libraries
	-$(RM) *.hex *.eep *.bin *.elf *.a *.ar *.d

size:
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-size" -A "./harvest-reservoir.elf"

project/main.cpp.o: ../../main.cpp project/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

project/main.cpp.d: ;

-include project/main.cpp.d 


core/wiring_digital.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_digital.c core/wiring_digital.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_digital.c.d: ;

-include core/wiring_digital.c.d

core/WString.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WString.cpp core/WString.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WString.cpp.d: ;

-include core/WString.cpp.d

core/CDC.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/CDC.cpp core/CDC.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/CDC.cpp.d: ;

-include core/CDC.cpp.d

core/Tone.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Tone.cpp core/Tone.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Tone.cpp.d: ;

-include core/Tone.cpp.d

core/wiring_shift.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_shift.c core/wiring_shift.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_shift.c.d: ;

-include core/wiring_shift.c.d

core/HardwareSerial2.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial2.cpp core/HardwareSerial2.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial2.cpp.d: ;

-include core/HardwareSerial2.cpp.d

core/USBCore.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/USBCore.cpp core/USBCore.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/USBCore.cpp.d: ;

-include core/USBCore.cpp.d

core/HardwareSerial1.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial1.cpp core/HardwareSerial1.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial1.cpp.d: ;

-include core/HardwareSerial1.cpp.d

core/IPAddress.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/IPAddress.cpp core/IPAddress.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/IPAddress.cpp.d: ;

-include core/IPAddress.cpp.d

core/WInterrupts.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WInterrupts.c core/WInterrupts.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/WInterrupts.c.d: ;

-include core/WInterrupts.c.d

core/wiring.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring.c core/wiring.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring.c.d: ;

-include core/wiring.c.d

core/wiring_pulse.S.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_pulse.S
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial.cpp core/HardwareSerial.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial.cpp.d: ;

-include core/HardwareSerial.cpp.d

core/wiring_analog.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_analog.c core/wiring_analog.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_analog.c.d: ;

-include core/wiring_analog.c.d

core/hooks.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/hooks.c core/hooks.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/hooks.c.d: ;

-include core/hooks.c.d

core/main.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/main.cpp core/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/main.cpp.d: ;

-include core/main.cpp.d

core/PluggableUSB.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/PluggableUSB.cpp core/PluggableUSB.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/PluggableUSB.cpp.d: ;

-include core/PluggableUSB.cpp.d

core/HardwareSerial0.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial0.cpp core/HardwareSerial0.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial0.cpp.d: ;

-include core/HardwareSerial0.cpp.d

core/Stream.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Stream.cpp core/Stream.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Stream.cpp.d: ;

-include core/Stream.cpp.d

core/new.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/new.cpp core/new.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/new.cpp.d: ;

-include core/new.cpp.d

core/WMath.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WMath.cpp core/WMath.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WMath.cpp.d: ;

-include core/WMath.cpp.d

core/HardwareSerial3.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial3.cpp core/HardwareSerial3.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial3.cpp.d: ;

-include core/HardwareSerial3.cpp.d

core/Print.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Print.cpp core/Print.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Print.cpp.d: ;

-include core/Print.cpp.d

core/abi.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/abi.cpp core/abi.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/abi.cpp.d: ;

-include core/abi.cpp.d

core/wiring_pulse.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_pulse.c core/wiring_pulse.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_pulse.c.d: ;

-include core/wiring_pulse.c.d



libraries/Wire/src/Wire.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/Wire.cpp libraries/Wire/src/Wire.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Wire/src/Wire.cpp.d: ;

-include libraries/Wire/src/Wire.cpp.d

libraries/Wire/src/utility/twi.c.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/utility/twi.c libraries/Wire/src/utility/twi.c.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Wire/src/utility/twi.c.d: ;

-include libraries/Wire/src/utility/twi.c.d

libraries/DallasTemperature/3.8.0/DallasTemperature.cpp.o: /home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0/DallasTemperature.cpp libraries/DallasTemperature/3.8.0/DallasTemperature.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/DallasTemperature/3.8.0/DallasTemperature.cpp.d: ;

-include libraries/DallasTemperature/3.8.0/DallasTemperature.cpp.d

libraries/SPI/src/SPI.cpp.o: /home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src/SPI.cpp libraries/SPI/src/SPI.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/SPI/src/SPI.cpp.d: ;

-include libraries/SPI/src/SPI.cpp.d

libraries/OneWire/2.3.4/OneWire.cpp.o: /home/jhahn/.arduinocdt/libraries/OneWire/2.3.4/OneWire.cpp libraries/OneWire/2.3.4/OneWire.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/OneWire/2.3.4/OneWire.cpp.d: ;

-include libraries/OneWire/2.3.4/OneWire.cpp.d

libraries/DHT_sensor_library/1.3.2/DHT.cpp.o: /home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2/DHT.cpp libraries/DHT_sensor_library/1.3.2/DHT.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/DHT_sensor_library/1.3.2/DHT.cpp.d: ;

-include libraries/DHT_sensor_library/1.3.2/DHT.cpp.d

libraries/DHT_sensor_library/1.3.2/DHT_U.cpp.o: /home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2/DHT_U.cpp libraries/DHT_sensor_library/1.3.2/DHT_U.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/DHT_sensor_library/1.3.2/DHT_U.cpp.d: ;

-include libraries/DHT_sensor_library/1.3.2/DHT_U.cpp.d

libraries/Ethernet/2.0.0/src/EthernetUdp.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/EthernetUdp.cpp libraries/Ethernet/2.0.0/src/EthernetUdp.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/EthernetUdp.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/EthernetUdp.cpp.d

libraries/Ethernet/2.0.0/src/EthernetServer.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/EthernetServer.cpp libraries/Ethernet/2.0.0/src/EthernetServer.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/EthernetServer.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/EthernetServer.cpp.d

libraries/Ethernet/2.0.0/src/socket.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/socket.cpp libraries/Ethernet/2.0.0/src/socket.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/socket.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/socket.cpp.d

libraries/Ethernet/2.0.0/src/Ethernet.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/Ethernet.cpp libraries/Ethernet/2.0.0/src/Ethernet.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/Ethernet.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/Ethernet.cpp.d

libraries/Ethernet/2.0.0/src/Dns.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/Dns.cpp libraries/Ethernet/2.0.0/src/Dns.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/Dns.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/Dns.cpp.d

libraries/Ethernet/2.0.0/src/Dhcp.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/Dhcp.cpp libraries/Ethernet/2.0.0/src/Dhcp.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/Dhcp.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/Dhcp.cpp.d

libraries/Ethernet/2.0.0/src/utility/w5100.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/utility/w5100.cpp libraries/Ethernet/2.0.0/src/utility/w5100.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/utility/w5100.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/utility/w5100.cpp.d

libraries/Ethernet/2.0.0/src/EthernetClient.cpp.o: /home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src/EthernetClient.cpp libraries/Ethernet/2.0.0/src/EthernetClient.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/jhahn/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/home/jhahn/.arduinocdt/libraries/aREST/2.7.4" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/jhahn/.arduinocdt/libraries/DallasTemperature/3.8.0" -I"/home/jhahn/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -I"/home/jhahn/.arduinocdt/libraries/OneWire/2.3.4" -I"/home/jhahn/.arduinocdt/libraries/DHT_sensor_library/1.3.2" -I"/home/jhahn/.arduinocdt/libraries/Ethernet/2.0.0/src" "$<" -o "$@"

libraries/Ethernet/2.0.0/src/EthernetClient.cpp.d: ;

-include libraries/Ethernet/2.0.0/src/EthernetClient.cpp.d

