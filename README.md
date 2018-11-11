# APOS (AVR Project Open Source)

Creates an AVR project template for Linux systems based on a Makefile.

This project is inspired by the avr-proj program Thatcher is incluye in the CrossPack AVR software package for MacOS.

It offers a free alternative with improvements and extra options, which works with Linux operating systems in a simple but very useful program.

## Content


- [Installation](#installation)
- [Toolchain Installation](#toolchain-installation)
- [Add udev rules](#add-udev-rules)
- [Usage](#usage)
	- [Project creation](#project-creation)
	- [APOS options](#apos-options)
	- [Project configuration](#project-configuration)
	- [Project compilation](#project-compilation)
	- [Add new sources to project ](#add-new-sources-to-project)
- [Makefile targets](#makefile-targets)
	- [Compile the code](#compile-the-code)
	- [Clean the compiled project](#clean-the-compiled-project)
	- [Flash the firmware](#flash-the-firmware)
	- [Erase chip](#erase-chip)
	- [Program reset](#program-reset)
	- [Write fuses](#write-fuses)
	- [Firmware install](#firmware-install)
	- [EEPROM file write](#eeprom-file-write)
	- [Read flash memory](#read-flash-memory)
	- [Read eeprom memory](#read-eeprom-memory)
	- [Disassemble the compiled code](#disassemble-the-compiled-code)


*****

## Installation

To install, dowload or clone this repository in your computer, then enter to the folder "apos" from the terminal and run the command "make" followed by the command "make install" as root: "sudo make install". 
It will install the program on your system:


```bash
$ git clone https://github.com/alfreedom/apos.git
$ cd apos
$ make
$ sudo make install
```
The default installation path is /opt/apos/. To check the installation run the command apos -? 

```bash
$ apos -?
```
or
```bash
$ apos -v
```

******

## Toolchain Installation

You need to have installed the avr-gcc toolchain and the avrdude program to compile your AVR source code. To install it run someone of the commands below depending of your operating system.
##### Debian and derivates
```bash
$ sudo apt-get install  gcc-avr binutils-avr avr-libc avrdude
```
##### Fedora and RedHat
```bash
$ sudo yum install  avr-gcc avr-binutils avr-libc avrdude
```
##### Arch and derivates
```bash
$ sudo pacman -Sy  avr-gcc avr-binutils avr-libc avrdude
```

## Add udev rules

To use the hardware programmers with avrdude without root permissions, 
it is necessary to add the rules of programmers to the system. Depending 
of your Linux distribution, you must change the name of the group to which the 
device rules belong. For Debian and derivatives the __*"dialout"*__ group is used, 
for Fedora it is __*"users"*__ and for Arch it is __*"uucp"*__.

The file must be created in the path "/etc/udev/rules.d/", with a name, for example, 
"90-avr.rules":

```bash
sudo nano /etc/udev/rules.d/90-avr.rules
```

And once the file is created, paste the following content by modifying the name of the group depending on the version of the operating system:

```bash
# Programmers for avrdude
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", GROUP="uucp", MODE="0660" # AVRISP mkII
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2107", GROUP="uucp", MODE="0660" # AVR-Dragon
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2103", GROUP="uucp", MODE="0660" # JTAG ICE mkII
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2106", GROUP="uucp", MODE="0660" # STK600
ATTR{idVendor}=="16c0", ATTR{idProduct}=="05dc", GROUP="uucp", MODE="0660" # USBASP von www.fischl.de
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2ffa", GROUP="uucp", MODE="0660" # AT90USB
ATTR{idVendor}=="10c4", ATTR{idProduct}=="ea60", GROUP="uucp", MODE="0660" # AVR910
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2105", GROUP="uucp", MODE="0660" # AVR ONE
ATTR{idVendor}=="03eb", ATTR{idProduct}=="210d", GROUP="uucp", MODE="0660" # Atmel XPLAIN CDC Gateway
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2ffb", GROUP="uucp", MODE="0660" # AT90USB AVR DFU bootloader
ATTR{idVendor}=="1781", ATTR{idProduct}=="0c9f", GROUP="uucp", MODE="0660" # usbtiny
```

To reload the device rules, execute the commands below:
```bash
sudo udevadm control --reload 
sudo udevadm trigger --action=add
```

## Usage 
This help show you how to create a project, configure it, and also how to add your own code. To create a new project run the command "apos" followed by the name of the project. 

This will create a folder containing the main.c file, the folders 'src', 'include' and the Makefile.

#### APOS options

	-ap         Define the ABOS Loader serial port (default: /dev/ttyUSB0)
	-ab         Define the ABOS Loader baudrate (default: 38400)
	-b          Creates a blink project template
	-m          Define the Microcontroller (default: atmega128)
	-ef         Defines the Extended Fuse  (2 digit hex format)
	-f          Define the CPU Frequency in Hz (default 16000000)
	-g          Initialize a GIT repository in the project folder
	-hf         Defines the High Fuse  (2 digit hex format)
	-lf         Defines the Low Fuse (2 digit hex format)
	-p          Defines the avrdude programmer (e.g usbasp, usbtiny, dragon_isp, etc.)
	-v          Shows the apos version
	-h, -?, ?   Shows help

#### Project creation
To create a empty project, type in a terminal the command:

```bash
$ apos my_proyect
```
Also, you could be defined another project params like the AVR Microcontroller model, the CPU Frequency, the fuses and the usb programmer. The program is able to create a blink example project and initialize the project with a Git repository,

To create a project for the ATmega328 that run at 16MHz and will be flashed with a USBtiny programmer, type in a terminal the command:

```bash
$ apos -d atmega328p -f 16000000 -p usbtiny my_proyect
```
If you want to create a git repository, add the "-g" option before the project name. In the same way add the "-b" option if you want to create the project with a blink program template.
<br>
#### Project Configuration
Do you need to change the microcontroller frequency, model, programmer, fuses or another configuration? you only need to edit the lines from 6 to 12 of the project Makefile.

```Makefile
 5
 6 PROJECT_NAME = my_project
 7 DEVICE       = atmega32
 8 CLOCK        = 16000000
 9 FUSES        = -U hfuse:w:0xD1:m -U lfuse:w:0xDE:m #-U efuse:w:0xFF:m
10 AVRDUDE      = avrdude
11 AVRDUDE_PROG = -c usbtiny -P usb
12 AVRDUDE_OPS  = -B 0.5 -D
13

```
#### Project Compilation 
To generate the .hex file, you need to open a terminal and go to the project folder, then type the command:

```bash
$ make
```
If all is ok, the compilation information will be shown in the terminal with usage data from the flash memory, ram and eeprom.
<br>
#### Add new sources to project 
Adding you own hardware drivers and libraries is very simple, only put your header file in the 'include' folder or another subfolder, and the source files in the 'src' folder or subfolder.

The final step is uncomment and copy the lines 15 and 19 of the 'Makefile' to add your source files and include paths.

```Makefile
13
14 OBJECT_FILES = main.o
15 #OBJECT_FILES += ./src/mySource.o
16
17 INCLUDEPATHS =  -I .
18 INCLUDEPATHS =  -I ./include
19 #INCLUDEPATHS += -I ./include/myFolder
20
```

Save changes and type "make" to compile your new code.
<br>
*****

## Makefile targets 
#### Compile the code
To compile the source code type the command:
```bash
$ make 
```
or
```bash
$ make all
```
#### Clean the compiled project
To clean (erase all compiled outputs) the project type the command:
```bash
$ make clean
```
#### Flash the firmware 
To program the flash memory of the AVR with the .hex file and the avrdude programmer configurated, type the command:
```bash
$ make flash
```
To program the AVR usign ABOS Bootloader, type the command:
```bash
$ make abos
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
To program the AVR fuses, the .hex program and the .eep eeprom file type the command:
```bash
$ make install
```
#### EEPROM file write
To program the AVR EEPROM memory whit the generate .eep file type the command:
```bash
$ make eeprom
```
#### Read flash memory
To read the contents of the flash memory type the command:
```bash
$ make read_flash
```
It will be generate a *.flash.bin file.
#### Read eeprom memory
To read the contents of the eeprom memory type the command:
```bash
$ make read_eeprom
```
It will be generate a *.eeprom.bin file.
#### Disassemble the compiled code
To disassemble the compiled .elf code type the command:
```bash
$ make disasm
```
***

Copyright © 2017-2018 Alfredo Orozco <alfredoopa@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
