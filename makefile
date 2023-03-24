#VARIABLES
CC = gcc
CFLAGS = -g -Wall -O2
SRC = main.c funciones.c funciones.h
OBJ = main.o funciones.o

#Reglas explicitas
all: $(OBJ)
	$(CC) $(CFLAGS) -o ejecutablemain $(OBJ)
clean:
	$(RM) $(OBJ) ejecutablemain

#Reglas implicitas
main.o: main.c funciones.h 
funciones.o: funciones.c