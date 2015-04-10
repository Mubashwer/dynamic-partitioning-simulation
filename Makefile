###
  # Name: Mubashwer Salman Khurshid
  # Username: mskh
  # StudentID: 601738
  #
  # Basic Makefile for comp30023 project1
  ##


## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS 	= -Wall  


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		memswap.c free_list.c process.c
OBJ =		memswap.o free_list.o process.o
EXE = 		memswap

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ) 

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE) 

## Dependencies

free_list.o:	free_list.h
process.o:	process.h
