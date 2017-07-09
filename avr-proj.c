#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define VERSION  			"1.2.1"
#define AUTHOR  			"Alfredo Orozco"
#define LAST_COMPILATION	"21-05-2017"


const char makefile_text[] = "\n# Name: Makefile\
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
\ninstall: flash fuse\
\n\
\nload: all\
\n	bootloadHID $(PROJECT_NAME).hex\
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

const char main_text[] = "/******************************************************\
\n * main.c\
\n *\
\n * Program Name:  Blink\
\n *       Author:  YOUR_NAME\
\n *         Date:  DATE\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n * 	Blink 8 leds connected on the PORTB of the AVR.\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n 	DDRB = 0xFF;	// PORTB as Output\
\n}\
\n\
\nint main()\
\n{\
\n 	// Initialize the AVR modules\
\n 	AVRInit();\
\n\
\n 	// Infinite loop\
\n 	while(1)\
\n 	{\
\n 		PORTB = 0xFF;		// PORTB High\
\n 		_delay_ms(1000);	// Wait 1s\
\n 		PORTB = 0x00;		// PORTB Low\
\n 		_delay_ms(1000);	// Wait 1s\
\n 	}\
\n\
\n 	return 0;\
\n}\
\n";

void show_help(char usage) {
	if(usage)
		printf("Usage: avr-proj <Project_Name>\n\n");
	printf("AVR project %s\nCreates an AVR project template whith a makefile using avr-gcc toolchain.\n", VERSION);
	printf("Created by %s <alfredoopa@gmail.com>\n", AUTHOR);

}

int main(int argc, char const *argv[])
{
	FILE *f;
	char txt[500];
	char aux[100];
	char file_content[4096];
	char prj_name[100];

	if(argc < 2) {
		show_help(1);
		return 0;
	}

	if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
		show_help(0);
		return 0;
	}

	strcpy(prj_name, argv[1]);
	for (int i = 0; i < strlen(prj_name); ++i)
	{
		if(prj_name[i]==' ')
			prj_name[i]= '_';
	}

	strcpy(aux,"\nPROJECT_NAME = ");
	strcat(aux,prj_name);

	mkdir(argv[1], 0700);
	strcpy(txt, argv[1]);
	strcat(txt, "/Makefile");
	f = fopen(txt, "w");

	strcpy(file_content, makefile_text);
	strcat(file_content, aux);
	strcat(file_content, makefile_text2);
	fwrite(file_content,sizeof(char), strlen(file_content), f);
	fclose(f);

	strcpy(txt, argv[1]);
	strcat(txt, "/main.c");
	f = fopen(txt, "w");
	fwrite(main_text,sizeof(char), strlen(main_text), f);
	fclose(f);

	strcpy(txt, argv[1]);
	strcat(txt, "/include");
	mkdir(txt, 0700);

	strcpy(txt, argv[1]);
	strcat(txt, "/src");
	mkdir(txt, 0700);
	
	return 0;
}
