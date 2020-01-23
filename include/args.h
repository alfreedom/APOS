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

// Struct to save the apos option arguments
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
	char abos_port[512];
	char abos_baudrate[512];
}options_t;

/**
 * Parse the comand line arguments and save the options in the
 * options_out param.
 * 
 * Return 1 if arguments are complete and correct, otherwise returns 0.
*/
int parse_args(int argc, char const *argv[], options_t *options_out){

	int ix;

	memset(options_out, 0, sizeof(options_t));
	// Set the default options
	strcpy(options_out->device, "atmega128");
	strcpy(options_out->f_cpu, "16000000");
	strcpy(options_out->programmer, "usbtiny");
	strcpy(options_out->high_f, "D9");
	strcpy(options_out->low_f, "FF");
	strcpy(options_out->extended_f, "FF");
	strcpy(options_out->abos_port, "/dev/ttyUSB0");
	strcpy(options_out->abos_baudrate, "38400");


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
				// Microcontroller Option
				case 'm': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->device, argv[i+1]);
					else
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] Microcontroller not specified in -m option\n\n" RESET);
						return 0;
					}
				break;
				// ABOS Options
				case 's': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->abos_baudrate, argv[i+1]);
					else
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] ABOS Serial Port not specified in -s option\n\n" RESET);
						return 0;
					}

				break;
				case 'p':
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->abos_port, argv[i+1]);
					else
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] ABOS Serial Port not specified in -p option\n\n" RESET);
						return 0;
					}
				break;
				// Low Fuse Option
				case 'l': 
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
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] Low Fuse not specified in -l option\n\n" RESET);
						return 0;
					}
				break;
				// High Fuse Option
				case 'h':
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
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] High Fuse not specified in -h option\n\n" RESET);
						return 0;
					}
				break;
				// Extended Fuse Option
				case 'e':
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
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] Extended Fuse not specified in -e option\n\n" RESET);
						return 0;
					}
				break;
				// CPU Frequency Option
				case 'f': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->f_cpu, argv[i+1]);
					else
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] CPU Frequency not specified in -f option\n\n" RESET);
						return 0;
					}
				break;
				case 'c': 
					if(i+1 < argc && argv[i+1][0] != '-') 
						strcpy(options_out->programmer, argv[i+1]);
					else
					{
						printf(RED "apos" RESET ": [" YELLOW "error" RESET "] AVRDUDE Programmer not specified in -p option\n\n" RESET);
						return 0;
					}
				break;
				// Version Option
				case 'v': options_out->version = 1; break;
				// Help Option
				case '?': options_out->help = 1; break;
				// Blink Option
				case 'b': options_out->blink_template = 1; break;
				// Git Repository Option
				case 'g': options_out->create_git = 1; break;
				// Invalid Option
				default: printf(RED "apos" RESET ": [" YELLOW "error" RESET "] invalid option " CYAN "%s\n\n" RESET, argv[i]);
								 return 0;
				
			}
		}
	}

	if(argv[argc-2][0] == '-' && (argv[argc-2][1] == 'v' || argv[argc-2][1] == '?' || argv[argc-2][1] == 'b' || argv[argc-2][1] == 'g' || argv[argc-2][1] == 'h'))
	{
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