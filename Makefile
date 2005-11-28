
all: oggfwd

oggfwd: oggfwd.c
	gcc -Wall -W -O20 -ffast-math -fsigned-char -lshout -lpthread -logg -lvorbis -ltheora oggfwd.c  -o oggfwd

clean:
	rm -f oggfwd

install: oggfwd
	install -m 755 oggfwd /usr/local/bin
