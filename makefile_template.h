
const char makefile_text1[] = "\n# Name: Makefile\
\n# Author:    <insert your name here>\
\n# Copyright: <insert your copyright message here>\
\n# License:   <insert your license reference here>\
\n";

const char makefile_text2[] = "\nDEVICE       = atmega328p\
\nCLOCK        = 16000000\
\nPROGRAMMER   = -c usbasp -P usb\
\nFUSES        = #-U hfuse:w:0xD9:m -U lfuse:w:0xDE:m\
\nAVRDUDE      = avrdude $(PROGRAMMER) -p $(DEVICE)\
\n\
\nOBJECT_FILES = main.o\
\n#OBJECT_FILES += ./src/mySource.o\
\n\
\nINCLUDEPATHS =  -I ./include\
\n\
\nCFLAGS = -ffunction-sections -fpermissive -std=c++11\
\nLDFLAGS = -Wl,-gc-sections\
\n\
\nCOMPILE = avr-g++ $(CFLAGS) $(LDFLAGS) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDEPATHS)\
\n\
\n# symbolic targets:\
\nall: $(PROJECT_NAME).hex\
\n\
\n.c.o:\
\n	$(COMPILE) -c $< -o $@\
\n\
\n.cpp.o:\
\n	$(COMPILE) -c $< -o $@\
\n\
\n.S.o:\
\n	$(COMPILE) -x assembler-with-cpp -c $< -o $@\
\n\
\n.c.s:\
\n	$(COMPILE) -S $< -o $@\
\n\
\n\
\n.cpp.s:\
\n	$(COMPILE) -S $< -o $@\
\n\
\nflash:	all\
\n	$(AVRDUDE) -U flash:w:$(PROJECT_NAME).hex:i\
\n\
\nfuse:\
\n	$(AVRDUDE) $(FUSES)\
\n\
\nerase:\
\n	$(AVRDUDE) -e\
\n\
\nreset:\
\n	$(AVRDUDE)\
\n\
\nerase:\
\n	$(AVRDUDE) -e\
\n\
\ninstall: flash fuse\
\n\
\nclean:\
\n	rm -f $(PROJECT_NAME).hex $(PROJECT_NAME).elf $(OBJECT_FILES)\
\n\
\n$(PROJECT_NAME).elf: $(OBJECT_FILES)\
\n	$(COMPILE) -o $(PROJECT_NAME).elf $(OBJECT_FILES)\
\n\
\n$(PROJECT_NAME).hex: $(PROJECT_NAME).elf\
\n	rm -f $(PROJECT_NAME).hex\
\n	avr-objcopy -j .text -j .data -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).hex\
\n	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf\
\n\
\ndisasm:	$(PROJECT_NAME).elf\
\n	avr-objdump -d $(PROJECT_NAME).elf\
\n\
\ncpp:\
\n	$(COMPILE) -E main.c\
\n" ;
