


all: apos.c
	gcc apos.c -o apos

clean:
	rm -f apos
	
install: all apos
	mkdir -p /opt/aposect
	cp apos /opt/aposect
	ln -f -s /opt/aposect/apos /usr/local/bin/apos