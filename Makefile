# Makefile
CC=gcc
CFLAGS=-lncurses -lpthread

sudoku: main.o sudoku.o
	$(CC) -o sudoku main.o sudoku.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
