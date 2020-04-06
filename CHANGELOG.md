# APOS Changelog

## [ 2.0.1 ] - APR 2020

#### Updated
  - Update the installation path for OSx.

#### Update
  - Change the help option, now is only --help. -? and ? cause problems in szh terminal.

## [ 2.0.0 ] - JAN 2020

#### Updated
  - Update examples in help screen.
  - Minor updates to default blink and makefile templates.

#### Changed
  - Change the name of command options to be only one letter.
     - avrdude programmer option "-p" now is "-c"
     - abos loader port option "-ap" now is "-p"
     - abos loader baudrate option "-ab" now is "-s"
     - extended fuse option "-ef" now is "-e"
     - high fuse option "-hf" now is "-h"
     - low fuse option "-lf" now is "-l"

#### Added
- Add default .gitignore file to proyectfolder with -g option.
- Add man page (1), now shows apos manual with *man apos*

## [ 1.8.0 ] - 2018-11-10

#### Added
- Add ABOS support to project creation
  - -ap: Specify the Serial Port for the ABOS Loader
  - -ab: Specify the Serial Port Baudrate for the ABOS Loader


## [ 1.7.0 ] - 2018-4-14

#### Added
- Add AVR eeprom code generation and programation.
- Add new Makefile targets
  - eeprom
  - read_eeprom
  - read_flash

#### Changed
* Changes the APOS license, now is GPL


## [ 1.6.0 ] - 2018-3-26

#### Updated
- Update APOS Help


## [ 1.5.0 ] - 2017-27-10

#### Updated
- Rename the project to APOS (AVR Project Open Source)


## [ 1.4.0 ] - 2017-27-10

#### Added
- Add git initialization to project creation
- Add blink template option
- Add options to configure the AVR model, frequency, avrdude programmer and fuses


## [ 1.3.1 ] - 2017-30-8

#### Added
- Add erase target to make file


## [ 1.3.0 ] - 2017-27-7

#### Added
- Add README.md

#### Updated
- Update the project structure to support basic templates


## [ 1.2.1 ] - 2017-8-7

#### Changed
- Change the default avrdude programmer to usbasp


## [ 1.2.0 ] - 2017-4-7

#### Added
- Add git initialization to project creation
- Add blink template option
- Add options to configure the AVR model, frequency, avrdude programmer and fuses


## [ 1.1.0 ] - 2017-22-6

#### Added
- Add include and src folders to better project organization

## [ 1.0.0 ] - 2017-21-5
First version of avr-proj tool for Linux