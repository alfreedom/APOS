
const char empty_template_body[] = "\n *       Author:  YOUR_NAME\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n *  YOUR PROGRAM DESCRIPTION HERE.\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n\
\n	// YOUR CODE INITIALIZATION\
\n\
\n}\
\n\
\nint main()\
\n{\
\n	// Initialize the AVR modules\
\n	AVRInit();\
\n\
\n	// Infinite loop\
\n	while(1)\
\n	{\
\n		// YOUR CODE HERE\
\n	}\
\n\
\n	return 0;\
\n}\
\n";


const char blink_program[] = "\n *       Author:  YOUR_NAME\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n *  Blink 8 leds connected on the PORTB of the AVR.\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n	DDRB = 0xFF;  // PORTB as Output\
\n}\
\n\
\nint main()\
\n{\
\n	// Initialize the AVR modules\
\n	AVRInit();\
\n\
\n	// Infinite loop\
\n	while(1)\
\n	{\
\n		PORTB = 0xFF;     // PORTB High\
\n		_delay_ms(1000);  // Wait 1s\
\n		PORTB = 0x00;     // PORTB Low\
\n		_delay_ms(1000);  // Wait 1s\
\n	}\
\n\
\n	return 0;\
\n}\
\n";


const char makefile_header[] = "# Name: Makefile\
\n# Author:    <insert your name here>\
\n# Copyright: <insert your copyright message here>\
\n# License:   <insert your license reference here>\
\n";

const char makefile_body[] = "\nAVRDUDE      = avrdude $(PROGRAMMER) -p $(DEVICE)\
\n\
\nOBJECT_FILES = main.o\
\n#OBJECT_FILES += ./src/mySource.o\
\n\
\nINCLUDEPATHS =  -I .\
\nINCLUDEPATHS += -I ./include\
\n#INCLUDEPATHS += -I ./include/myFolder\
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

