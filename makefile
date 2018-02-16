# Makefile de University
CFLAGS=-c -Wall

# Variables
CC = g++
EJECUTABLE = MAIN

# Programa Principal
all: node.h nodenario.h arbnario.h list.h  tail.h stack.h main.cpp
	$(CC) main.cpp -o $(EJECUTABLE)


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE) 
