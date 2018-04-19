/******************************************************************************
 *                                                                            *
 *    Copyright © 2017-2018 Alfredo Orozco <alfredoopa@gmail.com>                  *
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
 *****************************************************************************/

#include <stdio.h>

#define VERSION  			"1.7.0"
#define AUTHOR  			"Alfredo Orozco de la Paz"
#define AUTHOR_EMAIL		"alfredoopa@gmail.com"
#define LAST_COMPILATION	"April 19 2018"

#define RED				"\x1B[31m"
#define BOLD_RED		"\x1B[1;31m"
#define GREEN			"\x1B[32m"
#define BOLD_GREEN		"\x1B[1;32m"
#define YELLOW			"\x1B[33m"
#define BOLD_YELLOW		"\x1B[1;33m"
#define BLUE			"\x1B[34m"
#define BOLD_BLUE		"\x1B[1;34m"
#define MAGENTA			"\x1B[35m"
#define BOLD_MAGENTA	"\x1B[1;35m"
#define CYAN			"\x1B[36m"
#define BOLD_CYAN		"\x1B[1;36m"
#define WIHTE			"\x1B[37m"
#define BOLD_WIHTE		"\x1B[1;37m"
#define RESET			"\x1B[0m"
#define BOLD_RESET		"\x1B[1;0m"

/**
 * Print the APOS versión on the command line
*/
void show_version(){
	printf(RESET GREEN "\n APOS" RESET " (AVR Project Open Source)"BOLD_CYAN" v%s\n" BOLD_RESET" Last compilation: " BOLD_CYAN "%s\n", VERSION, LAST_COMPILATION);

	printf( BOLD_MAGENTA "      ___           ___           ___           ___     									\n");
	printf("     /\\  \\         /\\  \\         /\\  \\         /\\  \\    						\n");
	printf("    /::\\  \\       /::\\  \\       /::\\  \\       /::\\  \\   						\n");
	printf("   /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:/\\ \\  \\  				\n");
	printf(BOLD_CYAN "  /::\\~\\:\\  \\   /::\\~\\:\\  \\   /:/  \\:\\  \\   _\\:\\~\\ \\  \\ 		\n");
	printf(" /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\ /:/__/ \\:\\__\\ /\\ \\:\\ \\ \\__\\	\n");
	printf(" \\/__\\:\\/:/  / \\/__\\:\\/:/  / \\:\\  \\ /:/  / \\:\\ \\:\\ \\/__/			\n");
	printf("      \\::/  /       \\::/  /   \\:\\  /:/  /   \\:\\ \\:\\__\\  						\n");
	printf(BOLD_YELLOW"      /:/  /         \\/__/     \\:\\/:/  /     \\:\\/:/  /  								\n");
	printf("     /:/  /                     \\::/  /       \\::/  /   \n");
	printf("     \\/__/                       \\/__/         \\/__/    \n\n");

	printf(BOLD_CYAN " Creates an AVR project template based on a makefile.\n Uses the avr-gcc toolchain and avrdude.\n\n");
	printf(BOLD_RESET "   Usage:" BOLD_RED " apos " RESET "[" BOLD_YELLOW "OPTIONS" RESET "] <" BOLD_CYAN "Project_Name" RESET ">\n\n");
	printf(BOLD_YELLOW"   -?"RESET","BOLD_YELLOW " -h" RESET " or" BOLD_YELLOW" ? "RESET"option shows help\n\n");
}

/**
 * Shows the APOS help in the command line
*/
void show_help() {
	show_version();

	printf(BOLD_YELLOW "--------------------------------------------\n\n" RESET);
	printf(BOLD_YELLOW "   OPTIONS:\n\n" RESET);
	printf(YELLOW "     -b" RESET "       Create a blink project template\n");
	printf(YELLOW "     -ef" RESET "      Define the Extended Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -f" RESET "       Define the CPU Frequency (in Hz)\n");
	printf(YELLOW "     -g" RESET "       Initialize a GIT repository in the project folder\n");
	printf(YELLOW "     -hf" RESET "      Define the High Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -lf" RESET "      Define the Low Fuse (2 digit hex format)\n");
	printf(YELLOW "     -m" RESET "       Define the Microcontroller (e.g atmega328p)\n");
	printf(YELLOW "     -p" RESET "       Define the avrdude programmer (usbasp, usbtiny, dragon_isp, etc.)\n");
	printf(YELLOW "     -v" RESET "       Show the APOS version\n");
	printf(YELLOW "     -h,-?,? " RESET " Show this help\n\n");
	
	printf(BOLD_CYAN "--------------------------------------------\n\n" RESET);
	printf(BOLD_CYAN "   Makefile Options:\n\n" RESET);
	printf(CYAN "     all"  	 RESET "          Compile all the source file and generates the .hex file\n");
	printf(CYAN "     clean"   RESET "        Clean the project\n");
	printf(CYAN "     eeprom"  RESET "       Write the .eep file into the AVR eeprom memory\n");
	printf(CYAN "     erase"   RESET "        Erase the flash memory into the AVR\n");
	printf(CYAN "     flash"   RESET "        Write the .hex file into the AVR flash memory\n");
	printf(CYAN "     fuses"   RESET "        Program the low, high and extended fuses\n");
	printf(CYAN "     install" RESET "      Program the fuses, flash memory and eeprom data into the AVR\n");
	printf(CYAN "     reset"   RESET "        Resets the AVR microcontroller\n");
	printf(CYAN "     read_flash"  RESET "   Read the flash memory content and save it in a .bin file\n");
	printf(CYAN "     read_eeprom"  RESET "  Read the eeprom memory content and save it in a .bin file\n");
	printf(CYAN "     diasam"  RESET "       Disassemble the .hex file and generate the .asm file\n\n");
	
	printf(BOLD_MAGENTA "--------------------------------------------\n\n" RESET);
	printf(BOLD_MAGENTA "   Examples: create a blink project\n\n" RESET);
	printf("     Empty project:            " RED "apos " CYAN "blink\n" RESET);
	printf("     Create a Blink project:   " RED "apos " YELLOW "-b " CYAN "blink\n" RESET);
	printf("     Define MCU:               " RED "apos " YELLOW "-m " RESET "atmega32 " CYAN "blink\n" RESET);
	printf("     Define CPU frequency:     " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " CYAN "blink\n" RESET);
	printf("     Define programmer:        " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " CYAN "blink\n" RESET);
	printf("     Define fuses:             " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " YELLOW "-ef "RESET"ff "YELLOW"-lf "RESET"de "YELLOW"-hf "RESET"D9 "CYAN"blink\n" RESET);
	printf("                \n");
	printf(RESET" Created by " BOLD_CYAN "%s" MAGENTA " <" YELLOW "%s" MAGENTA ">\n\n" RESET, AUTHOR, AUTHOR_EMAIL);
	
}
