


all: avr-proj.c
	gcc avr-proj.c -o avr-proj

clean:
	rm -f avr-proj
	
install: avr-proj
	cp avr-proj /usr/local/bin