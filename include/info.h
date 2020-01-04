/******************************************************************************
 *   file: info.h                                                             *
 *                                                                            *
 *	 APOS                                                                     *
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

#include <stdio.h>

#define VERSION  			"2.0.0"
#define AUTHOR  			"Alfredo Orozco de la Paz"
#define AUTHOR_EMAIL		"alfredoopa@gmail.com"

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
	printf("APOS v%s (AVR Project Open Source)\n", VERSION);
}

/**
 * Shows the APOS help in the command line
*/
void show_help() {
	show_version();
	printf("\n");
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

	printf(BOLD_YELLOW "--------------------------------------------\n\n" RESET);
	printf(BOLD_YELLOW "   OPTIONS:\n\n" RESET);
	printf(YELLOW "     -b" RESET "       Create a blink project template\n");
	printf(YELLOW "     -c" RESET "       Define the avrdude programmer (default: usbtiny)\n");
	printf(YELLOW "     -e" RESET "       Define the Extended Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -f" RESET "       Define the CPU Frequency in Hz (default 16000000)\n");
	printf(YELLOW "     -g" RESET "       Initialize a GIT repository in the project folder\n");
	printf(YELLOW "     -h" RESET "       Define the High Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -l" RESET "       Define the Low Fuse (2 digit hex format)\n");
	printf(YELLOW "     -m" RESET "       Define the Microcontroller (default: atmega128)\n");
	printf(YELLOW "     -p" RESET "       Define the ABOS Loader serial port (default: /dev/ttyUSB0)\n");
	printf(YELLOW "     -s" RESET "       Define the ABOS Loader baudrate (default: 38400)\n");
	printf(YELLOW "     -v" RESET "       Show the APOS version\n");
	printf(YELLOW "     -?,? " RESET " Show this help\n\n");
	
	printf(BOLD_CYAN "--------------------------------------------\n\n" RESET);
	printf(BOLD_CYAN "   Makefile Options:\n\n" RESET);
	printf(CYAN "     abos"  	 RESET "         Write the .hex file into the AVR flash memory using ABOS Loader\n");
	printf(CYAN "     all"  	 RESET "          Compile all the source file and generates the .hex file\n");
	printf(CYAN "     clean"   RESET "        Clean the project\n");
	printf(CYAN "     eeprom"  RESET "       Write the .eep file into the AVR eeprom memory\n");
	printf(CYAN "     erase"   RESET "        Erase the flash memory into the AVR\n");
	printf(CYAN "     flash"   RESET "        Write the .hex file into the AVR flash memory usign avrdude\n");
	printf(CYAN "     fuses"   RESET "        Program the low, high and extended fuses\n");
	printf(CYAN "     install" RESET "      Program the fuses, flash memory and eeprom data into the AVR\n");
	printf(CYAN "     reset"   RESET "        Resets the AVR microcontroller\n");
	printf(CYAN "     read_flash"  RESET "   Read the flash memory content and save it in a .bin file\n");
	printf(CYAN "     read_eeprom"  RESET "  Read the eeprom memory content and save it in a .bin file\n");
	printf(CYAN "     diasam"  RESET "       Disassemble the .hex file and generate the .asm file\n\n");
	
	printf(BOLD_MAGENTA "--------------------------------------------\n\n" RESET);
	printf(BOLD_MAGENTA "   Examples: create a blink project\n\n" RESET);
	printf("     Empty project:            " RED "apos " CYAN "example\n" RESET);
	printf("     With git repository:      " RED "apos " YELLOW "-g " CYAN "example\n" RESET);
	printf("     Using usbtiny programmer: " RED "apos " YELLOW "-c " RESET "usbtiny " CYAN "example\n" RESET);
	printf("     Create a Blink project:   " RED "apos " YELLOW "-b " CYAN "blink\n" RESET);
	printf("     Define MCU:               " RED "apos " YELLOW "-m " RESET "atmega32 " CYAN "example\n" RESET);
	printf("     Define CPU frequency:     " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " CYAN "example\n" RESET);
	printf("     Define programmer:        " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " CYAN "example\n" RESET);
	printf("     Define fuses:             " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " YELLOW "-e "RESET"ff "YELLOW"-l "RESET"de "YELLOW"-h "RESET"D9 "CYAN"example\n" RESET);
	printf("     Define ABOS params:       " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p "RESET"/dev/ttyACM0 "YELLOW "-s " RESET "38400 "CYAN"example\n" RESET);
	printf("                \n");
	printf(RESET" Created by " BOLD_CYAN "%s" MAGENTA " <" YELLOW "%s" MAGENTA ">\n\n" RESET, AUTHOR, AUTHOR_EMAIL);
	
}
