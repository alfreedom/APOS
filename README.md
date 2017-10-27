# APOS - AVR Project Open Source
Creates an AVR project template for linux systems using makefile.

1. [Compiliation](#1-compilation)

2. [Installation](#2-installation)

3. [Usage](#3-usage)
	*[Project creation](#project-creation)
	*[Project configuration](#project-configuration)
	*[Project compilation](#project-compilation)
	*[Add new sources to project ](#add-new-sources-to-project)

4. [Makefile targets](#4-makefile-targets)
	*-[Flash the firmware](#flash-the-firmware)
	*-[Erase chip](#erase-chip)
	*.[Program reset](#program-reset)
	*-[Write fuses](#write-fuses)
	*-[Firmware install](#firmware-install)

*****

## 1. Compilation

To compile, you must enter in a terminal to the folder "avr-project" and type the command "make", this will generate de executable file.

```bash
$ make
```

*****

## 2. Installation

To install, run the command make install as root: "sudo make install". It will install the program on the system. The default installation path is /opt/avr-project/.

```bash
$ sudo make install

```

To verify the installation, run the command avr-proj -? 

```bash
$ avr-proj -?

```
o
```bash
$ avr-proj -v

```

******

## 3. Usage

This help show you how to create a project, configure it, and also how to add your own code. 
To create a new project run the command "avr-proj" followed by the name of the project. 
This will create a folder containing the main.c file, the folders 'src', 'include' and the Makefile.

#### Project creation 
To create a empty project, type in a terminal the command:

```bash
$ avr-proj my_blink

```
Also, you could be defined another project params like the AVR Microcontroller model, the CPU Frequency, the fuses and the usb programmer. The program is able to create a blink example project and initialize the project with a Git repository,

To create a project for the ATmega328 that run at 16MHz and will be flashed with a USBtiny programmer
type in a terminal the command:

```bash
$ avr-proj -d atmega328p -f 16000000 -p usbtiny hello_world

```
If you want to create a git repository, add the '-g' option before the project name. In the same way add the -b option if you want to create the project with a blink program tempalte.

#### Project Configuration
need you to change the microcontroller frequency, model, programmer, fuses or another configuration? you only need to edit the lines from 6 to 11 of the project Makefile.

#### Project Compilation 
To generate the .hex file, you need to open a terminal and move to the project folder, then type the command:

```bash
$ make

```
If all is ok, the compilation information will be shown in the terminal, with usage data from the flash memory, ram and eeprom.

#### Add new sources to project 
Adding you own hardware drivers and libraries is very simple, only put your header file in the 'include' folder or another subfolder, and the source files in the 'src' folder os subfolder.

The final step is uncomment and copy the lines 15 and 18 of the 'Makefile' to add your source files and include paths.

Save changes and type make to compile your new code.


*****

## 4. Makefile targets 
#### Compile the code
To compile the source code type the command:
```bash
$ make 

```
o
```bash
$ make all

```
#### Flash the firmware 
To flash the .hex program into the AVR microcontroller with the configurated programmer type the command:
```bash
$ make flash

```
#### Erase chip 
To erase the memories of the AVR type the command:
```bash
$ make erase

```
#### Program reset 
To reset the AVR microcontroller type the command:
```bash
$ make reset

```
#### Write fuses 
To program the AVR fuses configurated in the makefile type the command:
```bash
$ make fuses

```
#### Firmware install 
#### Write fuses 
To program the AVR fuses and the .hex program type the command:
```bash
$ make install

```


Autor: Alfredo Orozco de la Paz
