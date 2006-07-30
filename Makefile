PROG =		oggfwd
SRC =		oggfwd.c
MAN =		oggfwd.1

PREFIX ?=	/usr/local
BINDIR ?=	${PREFIX}/bin
MAN1DIR ?=	${PREFIX}/man/man1

CC ?=		gcc
CFLAGS ?=	-O2 -pipe
CFLAGS +=	-Wall -ffast-math -fsigned-char

INSTALL =	install

PTHREADFLAGS ?=	-pthread
INCLUDEFLAGS ?=	-I${PREFIX}/include
LINKFLAGS ?=	-L${PREFIX}/lib
LINKFLAGS +=    -lshout -logg -lvorbis -ltheora -lspeex

all: ${PROG}

${PROG}: ${SRC}
	${CC} ${CFLAGS} ${PTHREADFLAGS} ${INCLUDEFLAGS} ${LINKFLAGS} -o ${PROG} $<

install: ${PROG}
	${INSTALL} -c -m 555 -o root -g bin ${PROG} ${BINDIR}
	test -d ${MAN1DIR} || ${INSTALL} -d -o root ${MAN1DIR}
	${INSTALL} -c -m 444 -o root -g bin ${MAN} ${MAN1DIR}

clean:
	-@rm ${PROG} *~ core *.core
