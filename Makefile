


all: avr-proj.c
	gcc avr-proj.c -o avr-proj

install: avr-proj
	cp avr-proj /usr/local/bin