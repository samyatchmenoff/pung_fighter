SOURCES=$(wildcard *.c *.h)

all: pung_fighter

pung_fighter: $(SOURCES)
	gcc -o pung_fighter main.c moves.c `sdl2-config --libs --cflags` -framework OpenGL
