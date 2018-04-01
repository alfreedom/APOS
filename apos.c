#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "templates.h"

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

#define VERSION  			"1.6.3"
#define AUTHOR  			"Alfredo Orozco de la Paz"
#define AUTHOR_EMAIL		"alfredoopa@gmail.com"
#define LAST_COMPILATION	"April 1 2018"

typedef struct {
	char blink_template;
	char create_git;
	char version;
	char help;
	char f_cpu[20];
	char low_f[20];
	char high_f[20];
	char extended_f[20];
	char device[50];
	char programmer[50];
	char project_name[1024];
}options_t;

char txt[2048];

void show_version(){

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


	printf(RESET GREEN " APOS" RESET " (AVR Project Open Source)"BOLD_CYAN" v%s\n" BOLD_RESET" Last compilation: " BOLD_CYAN "%s\n\n", VERSION, LAST_COMPILATION);
	printf(" Creates an AVR project template based on a makefile.\n Uses the avr-gcc toolchain and avrdude.\n\n");
}

void show_help() {
	show_version();
	printf(BOLD_RESET "   Usage:" BOLD_RED " apos " RESET "[" BOLD_YELLOW "OPTIONS" RESET "] <" BOLD_CYAN "Project_Name" RESET ">\n\n");
	printf(BOLD_YELLOW"   -?"RESET" or"BOLD_YELLOW" ? "RESET"option Shows help\n\n");

	printf(BOLD_YELLOW "--------------------------------------------\n\n" RESET);
	printf(BOLD_YELLOW "   OPTIONS:\n\n" RESET);
	printf(YELLOW "     -b" RESET "    Create a blink project template\n");
	printf(YELLOW "     -ef" RESET "   Define the Extended Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -f" RESET "    Define the CPU Frequency (in Hz)\n");
	printf(YELLOW "     -g" RESET "    Initialize a GIT repository in the project folder\n");
	printf(YELLOW "     -hf" RESET "   Define the High Fuse  (2 digit hex format)\n");
	printf(YELLOW "     -lf" RESET "   Define the Low Fuse (2 digit hex format)\n");
	printf(YELLOW "     -m" RESET "    Define the Microcontroller (e.g atmega328p)\n");
	printf(YELLOW "     -p" RESET "    Define the avrdude programmer (e.g usbasp, usbtiny, dragon_isp, etc.)\n");
	printf(YELLOW "     -v" RESET "    Show the " RED "apos " RESET "version\n");
	printf(YELLOW "     -?,? " RESET " Show this help\n\n");
	
	printf(BOLD_CYAN "--------------------------------------------\n\n" RESET);
	printf(BOLD_CYAN "   Makefile Options:\n\n" RESET);
	printf(CYAN "     all"  	 RESET "        Compile all the source file and generates the .hex file\n");
	printf(CYAN "     clean"   RESET "      Clean the project\n");
	printf(CYAN "     erase"   RESET "      Erase the flash memory into the AVR\n");
	printf(CYAN "     fuses"   RESET "      Program the low, high and extended fuses\n");
	printf(CYAN "     install" RESET "    Program the fuses and flash memory into the AVR\n");
	printf(CYAN "     reset"   RESET "      Resets the AVR microcontroller\n");
	printf(CYAN "     disasm"  RESET "     Disassemble the .hex file and generate the .asm file\n\n");
	
	printf(BOLD_MAGENTA "--------------------------------------------\n\n" RESET);
	printf(BOLD_MAGENTA "   Examples: create a blink project\n\n" RESET);
	printf("     Empty project:            " RED "apos " CYAN "blink\n" RESET);
	printf("     Create a Blink project:   " RED "apos " YELLOW "-b " CYAN "blink\n" RESET);
	printf("     Define MCU:               " RED "apos " YELLOW "-m " RESET "atmega32 " CYAN "blink\n" RESET);
	printf("     Define CPU frequency:     " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " CYAN "blink\n" RESET);
	printf("     Define programmer:        " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " CYAN "blink\n" RESET);
	printf("     Define fuses:             " RED "apos " YELLOW "-m " RESET "atmega32 " YELLOW "-f " RESET "16000000 " YELLOW "-p " RESET "usbtiny " YELLOW "-e "RESET"ff "YELLOW"-l "RESET"de "YELLOW"-h "RESET"D9 "CYAN"blink\n" RESET);
	printf("                \n");
	printf(RESET" Created by " BOLD_CYAN "%s" MAGENTA " <" YELLOW "%s" MAGENTA ">\n\n" RESET, AUTHOR, AUTHOR_EMAIL);
	
}

int parse_args(int argc, char const *argv[], options_t *options_out){

	int ix;

	memset(options_out, 0, sizeof(options_t));
	// Set the default options
	strcpy(options_out->device, "atmega328p");
	strcpy(options_out->f_cpu, "16000000");
	strcpy(options_out->programmer, "usbtiny");
	strcpy(options_out->high_f, "D9");
	strcpy(options_out->low_f, "DE");
	strcpy(options_out->extended_f, "FF");

	for(int i = 1; i< argc; i++)
	{
		ix=0;
		char const *option = argv[i];
		if (*option == '?')
		{
			options_out->help = 1;
			return 1;
		}
		if(option[0] == '-')
		{
			if(!option[1])
			{
				printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
				return 0;
			}
			switch(option[1]){
				case 'm': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->device, argv[i+1]);
					else
						strcpy(options_out->device, "missing");
				break;
				case 'l': 
					if(!option[2] || option[2] != 'f')
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
						return 0;
					}
					if(i+1 < argc && argv[i+1][0] != '-') 
					{
						strcpy(options_out->low_f, argv[i+1]);
						while(options_out->low_f[ix])
						{
							options_out->low_f[ix] = toupper(options_out->low_f[ix]);							
							if(!isxdigit(options_out->low_f[ix]))
							{
								printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%c\"" RESET " for low fuses\n\n", options_out->low_f[ix]);
								return 0;
							}
							ix++;
						}
						if(strlen(options_out->low_f) >2)
						{
							printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%s\"" RESET " for low fuses, needs 2 digits\n\n" RESET, options_out->low_f);
							return 0;
						}
					}
					else
						strcpy(options_out->low_f, "missing");
				break;
				case 'h':
					if(!option[2] || option[2] != 'f')
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
						return 0;
					} 
					if(i+1 < argc && argv[i+1][0] != '-') 
					{
						strcpy(options_out->high_f, argv[i+1]);
						while(options_out->high_f[ix])
						{
							options_out->high_f[ix] = toupper(options_out->high_f[ix]);
							if(!isxdigit(options_out->high_f[ix]))
							{
								printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%c\"" RESET " for high fuses\n\n", options_out->high_f[ix]);
								return 0;
							}
							ix++;
						}
						if(strlen(options_out->high_f) >2)
						{
							printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%s\"" RESET " for high fuses, needs 2 digits\n\n" RESET, options_out->high_f);
							return 0;
						}
					}
					else
						strcpy(options_out->high_f, "missing");
				break;
				case 'e':
					if(!option[2] || option[2] != 'f')
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
						return 0;
					} 
					if(i+1 < argc && argv[i+1][0] != '-') 
					{
						strcpy(options_out->extended_f, argv[i+1]);
						while(options_out->extended_f[ix])
						{
							options_out->extended_f[ix] = toupper(options_out->extended_f[ix]);							
							if(!isxdigit(options_out->extended_f[ix]))
							{
								printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%c\"" RESET " for extended fuses\n\n", options_out->extended_f[ix]);
								return 0;
							}
							ix++;
						}
						if(strlen(options_out->extended_f) >2)
						{
							printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid hex value " CYAN "\"%s\"" RESET " for extended fuses, needs 2 digits\n\n" RESET, options_out->extended_f);
							return 0;
						}
					}
					else
						strcpy(options_out->extended_f, "missing");
				break;
				case 'f': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->f_cpu, argv[i+1]);
					else
						strcpy(options_out->f_cpu, "missing");
				break;
				case 'p': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->programmer, argv[i+1]);
					else
						strcpy(options_out->programmer, "missing");
				break;
				case 'v': options_out->version = 1; break;
				case '?': options_out->help = 1; break;
				case 'b': options_out->blink_template = 1; break;
				case 'g': options_out->create_git = 1; break;
				default: printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
				return 0;
				
			}
		}
	}

	if(argv[argc-2][0] == '-' && (argv[argc-2][1] == 'v' || argv[argc-2][1] == '?' || argv[argc-2][1] == 'b' || argv[argc-2][1] == 'g')){
		strcpy(options_out->project_name, argv[argc-1]);
	}
	else if(argv[argc-2][0] != '-' && argv[argc-1][0] != '-')
	{
			strcpy(options_out->project_name, argv[argc-1]);
	}
	else{
		if(!options_out->version && !options_out->help)
		{
			printf(RED "apos" RESET ": [" YELLOW "error" RESET "] missing project name\n\n" RESET);
			return 0;
		}
	}
	return 1;
}

void create_makefile(options_t *options) 
{
	FILE *f;
	// Creates the "Makefile" whit the content.
	strcpy(txt, options->project_name);
	strcat(txt, "/Makefile");
	f = fopen(txt, "w");
	
	fwrite(makefile_header,sizeof(char), strlen(makefile_header), f);
	fprintf(f, "\nPROJECT_NAME = %s\nDEVICE       = %s\nCLOCK        = %s\nPROGRAMMER   = -c %s -P usb\nFUSES        = -U hfuse:w:0x%s:m -U lfuse:w:0x%s:m #-U efuse:w:0x%s:m",
	options->project_name, options->device, options->f_cpu, options->programmer, options->high_f, options->low_f, options->extended_f);
	fwrite(makefile_body,sizeof(char), strlen(makefile_body), f);
	
	fclose(f);
}

void create_mainfile(options_t *options)
{
	FILE *f;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	strcpy(txt, options->project_name);
	strcat(txt, "/main.c");
	f = fopen(txt, "w");
	if(options->blink_template)
	{
		fprintf(f,"/******************************************************\n * main.c\n *\n * Program Name:  Blink\n *         Date:  %04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
		fwrite(blink_program, sizeof(char), strlen(blink_program), f);
	}
	else
	{
		fprintf(f,"/******************************************************\n * main.c\n *\n * Program Name:  %s\n *         Date:  %04d-%02d-%02d", options->project_name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
		fwrite(empty_template_body, sizeof(char), strlen(empty_template_body), f);
	}
	fclose(f);
}

void create_gitrepo(options_t *options)
{
	sprintf(txt, "cd %s && git init && git add * && git commit -m \"Initial commit for APOS AVR project ~%s~\"",options->project_name, options->project_name);
	system(txt);
}

void create_readme(options_t *options) 
{
		FILE *f;
		// Creates RREADME.md
		strcpy(txt, options->project_name);
		strcat(txt, "/README.md");
		f = fopen(txt, "w");
		fprintf(f, "\n# %s \n\n### Project created with APOS (AVR Project Open Source)\n\nTo edit the projecto settings, open the Makefile and edit the firs lines of the file.\n\n", options->project_name);
		fclose(f);
}

void create_folder_project(options_t *options)
{
	FILE *f;
	// Replace the spaces in the project name by "_", to avoid compilation problems
	for (int i = 0; i < strlen(options->project_name); ++i)
	{
		if(options->project_name[i]==' ')
			options->project_name[i]= '_';
	}

	if(f=fopen(options->project_name, "r"))
	{
		printf(BOLD_RED "\napos" RESET ": [" YELLOW "error" RESET "] the project " BOLD_YELLOW "\"%s\"" RESET " already exist!\n\n", options->project_name);
		
		fclose(f);
		exit(1);
	}
	// Creates the project folder with the name passed in the program arguments
	mkdir(options->project_name, 0700);
	// Creates the "include" folder
	strcpy(txt, options->project_name);
	strcat(txt, "/include");
	mkdir(txt, 0700);
	// Creates the "src" folder
	strcpy(txt, options->project_name);
	strcat(txt, "/src");
	mkdir(txt, 0700);
}

void create_project(options_t *options) 
{
	create_folder_project(options);
	create_makefile(options);
	create_mainfile(options);
	create_readme(options);
	if(options->create_git)
		create_gitrepo(options);

}

int main(int argc, char const *argv[])
{
	int parse_result;
	options_t options;

	// If not pass arguments to program show the help
	if(argc < 2) {
		show_version();
		return 0;
	}

	parse_result = parse_args(argc, argv, &options);

	if(options.version)
	{
		show_version();
		return 0;
	}
	if(options.help)
	{
		show_help();
		return 0;
	}
	if(!parse_result){
		printf("Write  apos " YELLOW "?" RESET " or " YELLOW "-?" RESET "  to see help.\n");
		return 0;
	}

	create_project(&options);
	
	printf(BOLD_GREEN  "\n  apos: Project \"%s\" created!\n", options.project_name);
	printf(BOLD_MAGENTA"\n  Project Information:\n\n");
	printf(BOLD_CYAN"   Project Name:    "BOLD_YELLOW"\"%s\"\n", options.project_name);
	printf(BOLD_CYAN"   Git Repository:  "BOLD_YELLOW"%s\n", options.create_git ? "True":"False");
	printf(BOLD_CYAN"   Blink Template:  "BOLD_YELLOW"%s\n", options.blink_template ? "True":"False");
	printf(BOLD_CYAN"   Microcontroller: "BOLD_YELLOW"%s\n", options.device);
	printf(BOLD_CYAN"   CPU Frequency:   "BOLD_YELLOW"%s\n", options.f_cpu);
	printf(BOLD_CYAN"   Low Fuse:        "BOLD_YELLOW"%s\n", options.low_f);
	printf(BOLD_CYAN"   High Fuse:       "BOLD_YELLOW"%s\n", options.high_f);
	printf(BOLD_CYAN"   Extended Fuse:   "BOLD_YELLOW"%s\n", options.extended_f);
	printf(BOLD_CYAN"   Programmer:      "BOLD_YELLOW"%s\n\n", options.programmer);




	return 0;
}
