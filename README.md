# APOS (AVR Project Open Source)

Creates an AVR project template for Linux systems based on a Makefile.

This project is inspired by the avr-proj program that includes the CrossPack for AVR software package for MacOS.

It offers a free alternative with improvements and extra options, which works with Linux operating systems in a simple but very useful program.

## Content


- [Installation](#installation)

- [Usage](#usage)
	- [Project creation](#project-creation)
	- [Project configuration](#project-configuration)
	- [Project compilation](#project-compilation)
	- [Add new sources to project ](#add-new-sources-to-project)


- [Makefile targets](#makefile-targets)
	- [Flash the firmware](#flash-the-firmware)
	- [Erase chip](#erase-chip)
	- [Program reset](#program-reset)
	- [Write fuses](#write-fuses)
	- [Firmware install](#firmware-install)

*****

## Installation

To install, dowload or clone this repository in your computer, the enter in a terminal to the folder "apos" and run the command "make" followed by the command "make install" as root: "sudo make install". 
It will install the program on the system:


```bash
$ git clone https://github.com/alfreedom/apos.git
$ cd apos
$ make
$ sudo make install
```
The default installation path is /opt/apos/. To verify the installation, run the command apos -? 

```bash
$ apos -?
```
or
```bash
$ apos -v
```

******

## Usage

This help show you how to create a project, configure it, and also how to add your own code. To create a new project run the command "apos" followed by the name of the project. 

This will create a folder containing the main.c file, the folders 'src', 'include' and the Makefile.

<span><span style="color: red;">*Important!</span> You need to have installed the avr-gcc toolchain and the avrdude program to compile the avr code. To install it run someone of the commands below depending of your operating system.
</span>
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

<br>

#### Add udev rules

To use the software programmers with avrdude without root permissions, 
it is necessary to add the rules of programmers to the system. Depending 
on the version of linux, you must change the name of the group to which the 
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

To reload the device rules, execute the below commands:
```bash
sudo udevadm control --reload 
sudo udevadm trigger --action=add
```
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
Do you need to change the microcontroller frequency, model, programmer, fuses or another configuration? you only need to edit the lines from 6 to 11 of the project Makefile.

```Makefile
 5
 6 PROJECT_NAME = my_project
 7 DEVICE       = atmega328p
 8 CLOCK        = 16000000
 9 PROGRAMMER   = -c usbasp -P usb
10 FUSES        = -U hfuse:w:0xD9:m -U lfuse:w:0xDE:m #-U efuse:w:0xFF:m
11 AVRDUDE      = avrdude $(PROGRAMMER) -p $(DEVICE)
12

```
#### Project Compilation 
To generate the .hex file, you need to open a terminal and go to the project folder, then type the command:

```bash
$ make
```
If all is ok, the compilation information will be shown in the terminal with usage data from the flash memory, ram and eeprom.
<br>
#### Add new sources to project 
Adding you own hardware drivers and libraries is very simple, only put your header file in the 'include' folder or another subfolder, and the source files in the 'src' folder os subfolder.

The final step is uncomment and copy the lines 14 and 17 of the 'Makefile' to add your source files and include paths.

```Makefile
12
13 OBJECT_FILES = main.o
14 #OBJECT_FILES += ./src/mySource.o
15
16 INCLUDEPATHS =  -I ./include
17 #INCLUDEPATHS += -I ./include/myFolder
18
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
#### Flash the firmware 
To program the flash memory of the AVR with the .hex file and the programmer configurated, type the command:
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
To program the AVR fuses and the .hex program type the command:
```bash
$ make install
```
***
Autor: Alfredo Orozco de la Paz
