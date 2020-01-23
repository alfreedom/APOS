/******************************************************************************
 *   file: args.h                                                             *
 *                                                                            *
 *	 AVR Project Open Source (APOS)                                                                     *
 *                                                                            *
 *   This program is free software: you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation, either version 3 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>     *
 *                                                                            *
 *   Written by Alfredo Orozco <alfredoopa@gmail.com>                         *
 *****************************************************************************/

const char gitignore[] = "\n# Ignored files and foldes\
\n*.o\
\n*.elf\
\n}\
\n";
const char empty_template_body[] = "\n *       Author:  YOUR_NAME\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n *  This is my program description..\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n	// AVR Initialization\
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
\n\
\n	}\
\n\
\n	return 0;\
\n}\
\n";


const char blink_program[] = "\n *       Author:  YOUR_NAME\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n *  Blink a led connected on the PORTG 0 of the AVR.\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n	DDRG = 0x01;  // PORTG 0 as Output\
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
\n		PORTG |= 0x01;     // PORTB 0 High\
\n		_delay_ms(1000);  // Wait 1s\
\n		PORTG &= ~0x01;     // PORTB 0 Low\
\n		_delay_ms(1000);  // Wait 1s\
\n	}\
\n\
\n	return 0;\
\n}\
\n";


const char makefile_apos_header[] = "#############################################\
\n# 				APOS Makefile				#\
\n#											#\
\n#############################################\n";

const char makefile_apos_body[] = "\
\nAVRDUDE_OPS   = -B 0.5\
\nAVRDUDE       = avrdude -p $(DEVICE) $(AVRDUDE_PROG) $(AVRDUDE_OPS)\
\n\
\nOBJECT_FILES = main.o\
\n#OBJECT_FILES += ./src/mySource.o\
\n\
\nINCLUDEPATHS =  -I .\
\nINCLUDEPATHS += -I ./lib\
\n#INCLUDEPATHS += -I ./myFolder\
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
\nabos:	$(PROJECT_NAME).hex \
\n	abosl --port=$(ABOS_PORT) --cpu $(DEVICE) --baudrate=$(ABOS_BAUDRATE) $(PROJECT_NAME).hex\
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
\neeprom:	$(PROJECT_NAME).eep\
\n	$(AVRDUDE) -U eeprom:w:$(PROJECT_NAME).eep:i\
\n\
\nread_eeprom:\
\n	$(AVRDUDE) -U eeprom:r:$(PROJECT_NAME).eeprom.bin:r\
\n\
\nread_flash:\
\n	$(AVRDUDE) -U flash:r:$(PROJECT_NAME).flash.bin:r\
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
\n	avr-objcopy -j .eeprom --set-section-flags=.eeprom=\"alloc,load\" --change-section-lma .eeprom=0 -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).eep\
\n	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf\
\n\
\ndisasm:	$(PROJECT_NAME).elf\
\n	avr-objdump -d $(PROJECT_NAME).elf\
\n\
\ncpp:\
\n	$(COMPILE) -E main.c\
\n" ;


