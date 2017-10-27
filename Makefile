


all: avr-proj.c
	gcc avr-proj.c -o avr-proj

clean:
	rm -f avr-proj
	
install: avr-proj
	mkdir -p /opt/avr-project
	cp avr-proj /opt/avr-project
	ln -f -s /opt/avr-project/avr-proj /usr/local/bin/avr-proj