# APOS - AVR Project Open Source
Creates an AVR project template for linux systems using makefile.

1. [Compiliation](#user-content-compilation)

2. [Installation](#user-content-installation)

3. [Usage](#user-content-usage)
[Project creation](#user-content-creating-new-project)
[Project configuration](#user-content-creating-new-project)
[Project compilation](#user-content-compile-the-project)
[Add sources to project](#user-content-add-sourcer-to-project)
[Add include paths to project](#user-content-creating-new-project)
[Programmer configuration](#user-content-configure-the-programmer)

4. [Makefile targets](#user-content-configure-the-programmer)
[Flash the firmware](#user-content-configure-the-programmer)
[Erase chip](#user-content-configure-the-programmer)
[Program reset](#user-content-configure-the-programmer)
[Write fuses](#user-content-configure-the-programmer)
[Firmware install](#user-content-configure-the-programmer)

*****
*****

## 1. Compilation

To compile, you must enter in a terminal to the folder "avr-project" and type the command "make", this will generate de executable file.

```bash
$ make
```

*****
*****

## 2. Installation

To install, run the command make install as administrator: "sudo make install". It will install the program on the system. The default
installation path is /usr/local/bin.

```bash
$ sudo make install

```

******
******

## 3. Usage

This help show you how to create a project, configure it, and also how to add your own libraries 
To create a new project run the command "avr-proj" followed by the name of the project. 
This will create a folder containing the main.c file and the Makefile.
Once that the project has been created, just type the command "make" and the AVR project will be compiled.

Autor: Alfredo Orozco de la Paz

#### Project creation 
#### Project Configuration
#### Project Compilationt 
#### Add sources to project 
#### Add include paths to project 
#### Programmer configuration 

*****
*****

## 4. Makefile targets 
#### Flash the firmware 
#### Erase chip 
#### Program reset 
#### Write fuses 
#### Firmware install 