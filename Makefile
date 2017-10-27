all: apos.c
	gcc apos.c -o apos

clean:
	rm -f apos
	
install: all apos
	mkdir -p /opt/apos
	cp apos /opt/apos
	ln -f -s /opt/apos/apos /usr/local/bin/apos