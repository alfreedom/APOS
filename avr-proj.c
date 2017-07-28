#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "blank_program.h"
#include "blink_program.h"
#include "makefile_template.h"

#define VERSION  			"1.4.0"
#define AUTHOR  			"Alfredo Orozco de la Paz <alfredoopa@gmail.com>"
#define LAST_COMPILATION	"27-07-2017"


void show_help(char usage) {
	printf("AVR Project v%s\n", VERSION);
	printf("Creates an AVR project template based on a makefile using avr-gcc toolchain.\n\n");
	if(usage)
		printf("   Usage: avr-proj <Project_Name>\n\n");

	printf("Created by %s\n", AUTHOR);

}

int main(int argc, char const *argv[])
{
	FILE *f;
	char txt[2048];
	char aux[2048];
	char file_content[4096];
	char prj_name[2048];

	// If not pass arguments to program show the help
	if(argc < 2) {
		show_help(1);
		return 0;
	}

	//if the program arguments are "-v" or "--version" show the versión

	if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
		show_help(0);
		return 0;
	}

	// Get the project name from the arguments
	strcpy(prj_name, argv[1]);

	// Replace the spaces in the project name by "_", to avoid compilation problems
	for (int i = 0; i < strlen(prj_name); ++i)
	{
		if(prj_name[i]==' ')
			prj_name[i]= '_';
	}

	// Sets the project name for the makefile
	strcpy(aux, "\nPROJECT_NAME = ");
	strcat(aux, prj_name);

	if(f=fopen(argv[1], "r")){
		printf("avr-proj: [error] The project \"%s\" already exist!\n", argv[1]);
		fclose(f);
		return 0;
	}

	// Creates the project folder with the name passed in the program arguments
	mkdir(argv[1], 0700);


	// Generates the "Makefile" content for the project.
	strcpy(file_content, makefile_text1);
	strcat(file_content, aux);
	strcat(file_content, makefile_text2);

	// Creates the "Makefile" whit the content.
	strcpy(txt, argv[1]);
	strcat(txt, "/Makefile");
	f = fopen(txt, "w");
	fwrite(file_content,sizeof(char), strlen(file_content), f);
	fclose(f);

	// Creates the "README.md".
	strcpy(txt, argv[1]);
	strcat(txt, "/README.md");
	f = fopen(txt, "w");
	strcpy(txt, "\n# ");
	strcat(txt, argv[1]);
	strcat(txt, "\n\n");
	strcat(txt, "\n### Project created whit APOS (AVR Project Open Source)\n");
	fwrite(txt,sizeof(char), strlen(txt), f);
	fclose(f);

	// Generate and creates the "main.c" file for the project. This is a basic blink example
	strcpy(txt, argv[1]);
	strcat(txt, "/main.c");
	f = fopen(txt, "w");
	fwrite(blink_program, sizeof(char), strlen(blink_program), f);
	fclose(f);

	// Creates the "include" folder
	strcpy(txt, argv[1]);
	strcat(txt, "/include");
	mkdir(txt, 0700);

	// Creates the "src" folder
	strcpy(txt, argv[1]);
	strcat(txt, "/src");
	mkdir(txt, 0700);
	
	printf("avr-proj: Project \"%s\" created!\n", argv[1]);

	strcpy(txt, "cd ");
	strcat(txt, argv[1]);
	strcat(txt, " && git init");
	system(txt);


	return 0;
}
