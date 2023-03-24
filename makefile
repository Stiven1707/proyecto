#VARIABLES
CC = gcc
CFLAGS = -g -Wall -O2 -pthread
SRC = main.c funciones.c funciones.h
OBJ = main.o funciones.o

#Reglas explicitas
all: $(OBJ)
	$(CC) $(CFLAGS) -o ejecutablemain $(OBJ)
	gcc client.c -o client
clean:
	$(RM) $(OBJ) ejecutablemain client

#Reglas implicitas
main.o: main.c funciones.h 
funciones.o: funciones.c