
all: main.c
	gcc main.c -o apos

clean:
	rm -f apos
	
install: all apos
	mkdir -p /opt/apos
	cp apos /opt/apos
	ln -f -s /opt/apos/apos /usr/local/bin/apos

dev-debian:
	apt-get install gcc-avr binutils-avr avr-libc avrdude
	cp debian.rules /etc/udev/rules.d/90-avr.rules
	udevadm control --reload
	udevadm trigger --action=add

dev-arch:
	pacman -Sy avr-gcc avr-binutils avr-libc avrdude
	cp arch.rules /etc/udev/rules.d/90-avr.rules
	udevadm control --reload
	udevadm trigger --action=add

dev-fedora:
	yum install avr-gcc avr-binutils avr-libc avrdude
	cp fedora.rules /etc/udev/rules.d/90-avr.rules
	udevadm control --reload
	udevadm trigger --action=add
