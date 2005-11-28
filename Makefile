PREFIX=/usr
INSTALL=install

all: oggfwd

oggfwd: oggfwd.c
	gcc -Wall -O2 -ffast-math -fsigned-char -lshout -lpthread -logg -lvorbis -ltheora oggfwd.c  -o oggfwd

install: oggfwd
	$(INSTALL) -D -m 755 oggfwd $(PREFIX)/bin/oggfwd		

clean:
	rm -f oggfwd
