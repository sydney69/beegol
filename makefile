# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c)

all:
	gcc -std=c99 $(SRC) -o beegol
