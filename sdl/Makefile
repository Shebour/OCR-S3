CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CLFAGS= -Wall -Wextra -Werror -std=c99 -O1
LDFLAGS=
LDLIBS= `pkg-config --libs sdl2` -lSDL2_image

SRC = *.c
OBJ = ${SRC: .c=.o}

main: ${OBJ}

directory:
	mkdir -p Lettres

clean:
	${RM} *.o 
	${RM} main
	${RM} *.d
	rm -rf Lettres/
