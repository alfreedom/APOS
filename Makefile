##############################################################################
#   file: Makefile                                                           #
#                                                                            #
#	AVR Project Open Source (APOS)                                                                     #
#                                                                            #
#   This program is free software: you can redistribute it and/or modify     #
#   it under the terms of the GNU General Public License as published by     #
#   the Free Software Foundation, either version 3 of the License, or        #
#   (at your option) any later version.                                      #
#                                                                            #
#   This program is distributed in the hope that it will be useful,          #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of           #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
#   GNU General Public License for more details.                             #
#                                                                            #
#   You should have received a copy of the GNU General Public License        #
#   along with this program.  If not, see <http://www.gnu.org/licenses/>     #
#                                                                            #
#   Written by Alfredo Orozco <alfredoopa@gmail.com>                         #
##############################################################################

all: main.c
	gcc main.c -o apos

clean:
	rm -f apos
	
install: all apos
	mkdir -p /opt/apos
	cp apos /opt/apos
	ln -f -s /opt/apos/apos /usr/local/bin/apos
	cp apos.1 /usr/local/share/man/man1/
	
install-osx: all apos
	mkdir -p /opt/apos
	cp apos /opt/apos
	ln -f -s /opt/apos/apos /usr/local/bin/apos
	cp apos.1 /usr/local/share/man/man1/

dev-debian:
	apt-get remove modemmanager
	adduser $USER dialout
	apt-get install gcc-avr binutils-avr avr-libc avrdude
	cp debian.rules /etc/udev/rules.d/90-avr.rules
	cp apos.1 /usr/local/share/man/man1/
	udevadm control --reload
	udevadm trigger --action=add

dev-arch:
	pacman -Sy avr-gcc avr-binutils avr-libc avrdude
	cp arch.rules /etc/udev/rules.d/90-avr.rules
	cp apos.1 /usr/local/share/man/man1/
	udevadm control --reload
	udevadm trigger --action=add

dev-fedora:
	yum install avr-gcc avr-binutils avr-libc avrdude
	cp fedora.rules /etc/udev/rules.d/90-avr.rules
	cp apos.1 /usr/local/share/man/man1/
	udevadm control --reload
	udevadm trigger --action=add
