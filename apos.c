#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "templates.h"

#define VERSION  			"1.5"
#define AUTHOR  			"Alfredo Orozco de la Paz <alfredoopa@gmail.com>"
#define LAST_COMPILATION	"26-10-2017"

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
	printf("APOS (AVR Project Open Source) v%s\n\n", VERSION);
	printf("Creates an AVR project template based on a makefile using avr-gcc toolchain.\n\n");
}
void show_help() {
	show_version();
	printf("   Usage: apos [OPTIONS] <Project_Name>\n\n");
	printf("   OPTIONS:\n\n");
	printf("     -b         Create a blink project template.\n");
	printf("     -d         Define the Microcontroller (e.g atmega328p).\n");
	printf("     -e         Define the Extended Fuse  (2 digit hex format).\n");
	printf("     -f         Define the CPU Frequency (in Hz).\n");
	printf("     -g         Initialize a GIT repository in the project folder.\n");
	printf("     -h         Define the Low Fuse  (2 digit hex format).\n");
	printf("     -l         Define the High Fuse (2 digit hex format).\n");
	printf("     -p         Define the avrdude programmer (e.g usbasp, usbtiny, dragon_isp, etc.).\n");
	printf("     -v         Show the apos version.\n");
	printf("     -?         Show this help.\n\n");
	
	printf("   Makefile Options:\n\n");
	printf("     all        Compile al the source file and generates the .hex file.\n");
	printf("     clean      Clean the project.\n");
	printf("     erase      Erase the flash memory into the AVR\n");
	printf("     fuses      Program the low, high and extended fuses.\n");
	printf("     install    Program the fuses and flash memory into the AVR\n");
	printf("     reset      Resets the AVR microcontroller.\n");
	printf("     disasm     Disassemble the .hex file and generate de .asm file.\n\n");
	
	printf("   Usage example: create a blink project\n\n");
	printf("     Empty Project:            apos blink\n");
	printf("     Create a Blink Project:   apos -b blink\n");
	printf("     Define MCU:               apos -d atmega32 blink\n");
	printf("     Define F_CPU:             apos -d atmega32 -f 16000000 blink\n");
	printf("     Define Programmer:        apos -d atmega32 -f 16000000 -p usbtiny blink\n");
	printf("     Define Fuses:             apos -d atmega32 -f 16000000 -p usbtiny -e ff -l de -h D9 blink\n");
	printf("                \n");
	printf(" Created by %s\n", AUTHOR);

}

int parse_args(int argc, char const *argv[], options_t *options_out){

	memset(options_out, 0, sizeof(options_t));
	// Set the default options
	strcpy(options_out->device, "atmega328p");
	strcpy(options_out->f_cpu, "16000000");
	strcpy(options_out->programmer, "usbasp");
	strcpy(options_out->high_f, "D9");
	strcpy(options_out->low_f, "DE");
	strcpy(options_out->extended_f, "FF");

	for(int i = 1; i< argc; i++)
	{
		char const *option = argv[i];
		if(option[0] == '-')
		{
			if(!option[1])
			{
				printf("apos: [error] invalid option %s\n\n", argv[i]);
				return 0;
			}
			switch(option[1]){
				case 'd': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->device, argv[i+1]);
					else
						strcpy(options_out->device, "missing");
				break;
				case 'l': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->low_f, argv[i+1]);
					else
						strcpy(options_out->low_f, "missing");
				break;
				case 'h': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->high_f, argv[i+1]);
					else
						strcpy(options_out->high_f, "missing");
				break;
				case 'e': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->extended_f, argv[i+1]);
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
				default: printf("apos: [e_rror] invalid option %s\n\n", argv[i]);
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
			printf("apos: [error] missing project name\n\n");
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
		fprintf(f,"/******************************************************\n * main.c\n *\n * Program Name:  Blink\n *         Date:  %d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
		fwrite(blink_program, sizeof(char), strlen(blink_program), f);
	}
	else
	{
		fprintf(f,"/******************************************************\n * main.c\n *\n * Program Name:  %s\n *         Date:  %d-%d-%d", options->project_name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
		fwrite(empty_template_body, sizeof(char), strlen(empty_template_body), f);
	}
	fclose(f);
}

void create_gitrepo(options_t *options)
{
	sprintf(txt, "cd %s && git init && git add * && git commit -m \"Initial commit for the AVR project ~%s~\"",options->project_name, options->project_name);
	system(txt);
}

void create_readme(options_t *options) 
{
		FILE *f;
		// Creates RREADME.md
		strcpy(txt, options->project_name);
		strcat(txt, "/README.md");
		f = fopen(txt, "w");
		fprintf(f, "\n# %s \n\n### Project created with APOS (AVR Project Open Source)\n\nTo edit the projecto settings, open the Makefile and edit the firs lines of the file.", options->project_name);
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
		printf("apos: [error] The project \"%s\" already exist!\n", options->project_name);
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
		show_help();
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
		printf("Write  apos -?  to see help.\n");
		return 0;
	}

	printf("Project Information:\n\n");
	printf("  *Project Name:    %s\n", options.project_name);
	printf("  *Git Repository:  %s\n", options.create_git ? "True":"False");
	printf("  *Blink Template:  %s\n", options.blink_template ? "True":"False");
	printf("  *Microcontroller: %s\n", options.device);
	printf("  *CPU Frequency:   %s\n", options.f_cpu);
	printf("  *Low Fuse:        %s\n", options.low_f);
	printf("  *High Fuse:       %s\n", options.high_f);
	printf("  *Extended Fuse:   %s\n", options.extended_f);
	printf("  *Programmer:      %s\n\n", options.programmer);


	create_project(&options);

	printf("\napos: Project \"%s\" created!\n\n", options.project_name);

	return 0;
}
