#############################################
# 				APOS Makefile				#
#											#
#############################################

PROJECT_NAME  = man
DEVICE        = atmega128
CLOCK         = 16000000
FUSES         = -U hfuse:w:0xD9:m -U lfuse:w:0xFF:m -U efuse:w:0xFF:m
AVRDUDE_PROG  = -c usbtiny -P usb
ABOS_PORT     = /dev/ttyUSB0
ABOS_BAUDRATE = 38400
AVRDUDE_OPS   = -B 0.5
AVRDUDE       = avrdude -p $(DEVICE) $(AVRDUDE_PROG) $(AVRDUDE_OPS)

OBJECT_FILES = main.o
#OBJECT_FILES += ./src/mySource.o

INCLUDEPATHS =  -I .
INCLUDEPATHS += -I ./lib
#INCLUDEPATHS += -I ./myFolder

CFLAGS = -ffunction-sections -fpermissive -std=c++11
LDFLAGS = -Wl,-gc-sections

COMPILE = avr-g++ $(CFLAGS) $(LDFLAGS) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDEPATHS)

# symbolic targets:
all: $(PROJECT_NAME).hex

.c.o:
	$(COMPILE) -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

.cpp.s:
	$(COMPILE) -S $< -o $@

abos:	$(PROJECT_NAME).hex 
	abosl --port=$(ABOS_PORT) --cpu $(DEVICE) --baudrate=$(ABOS_BAUDRATE) $(PROJECT_NAME).hex

flash:	all
	$(AVRDUDE) -U flash:w:$(PROJECT_NAME).hex:i

fuse:
	$(AVRDUDE) $(FUSES)

erase:
	$(AVRDUDE) -e

reset:
	$(AVRDUDE)

eeprom:	$(PROJECT_NAME).eep
	$(AVRDUDE) -U eeprom:w:$(PROJECT_NAME).eep:i

read_eeprom:
	$(AVRDUDE) -U eeprom:r:$(PROJECT_NAME).eeprom.bin:r

read_flash:
	$(AVRDUDE) -U flash:r:$(PROJECT_NAME).flash.bin:r
install: flash fuse

clean:
	rm -f $(PROJECT_NAME).hex $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).elf: $(OBJECT_FILES)
	$(COMPILE) -o $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	rm -f $(PROJECT_NAME).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).eep
	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf

disasm:	$(PROJECT_NAME).elf
	avr-objdump -d $(PROJECT_NAME).elf

cpp:
	$(COMPILE) -E main.c
