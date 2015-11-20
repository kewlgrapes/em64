# Makefile
#   Nick Becker
#   19 November, 2015

# make
# make clean

# configuration
CC = gcc
CFLAGS = -c
LFLAGS =

# directories
BIN = bin
SRC = src
OBJ = obj

# main executables
em64: $(OBJ)/em64.o
	$(CC) $(LFLAGS) $(OBJ)/em64.o $(OBJ)/cpu.o $(OBJ)/memory.o $(OBJ)/graphics.o -o $(BIN)/em64

# objects
$(OBJ)/em64.o: $(SRC)/em64.c $(OBJ)/cpu.o $(OBJ)/memory.o $(OBJ)/graphics.o
	$(CC) $(CFLAGS) $(SRC)/em64.c -o $(OBJ)/em64.o

$(OBJ)/cpu.o: $(SRC)/cpu.c $(SRC)/cpu.h
	$(CC) $(CFLAGS) $(SRC)/cpu.c -o $(OBJ)/cpu.o

$(OBJ)/memory.o: $(SRC)/memory.c $(SRC)/memory.h
	$(CC) $(CFLAGS) $(SRC)/memory.c -o $(OBJ)/memory.o

$(OBJ)/graphics.o: $(SRC)/graphics.c $(SRC)/graphics.h
	$(CC) $(CFLAGS) $(SRC)/graphics.c -o $(OBJ)/graphics.o
