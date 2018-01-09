# Makefile for programs
#******************************************************************************

PROGRAMS = sudokuChecker 

#******************************************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS =

#******************************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

#******************************************************************************
# Standard entries to remove files from the directories
# 	tidy -- eliminate unwanted files
#	scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps
		
scratch:
	rm -f *.o *.a $(PROGRAMS)

#******************************************************************************
# C compilations

sudokuChecker.o: sudokuChecker.c sudokuChecker.h
	$(CC) $(CFLAGS) -c sudokuChecker.c
	
#******************************************************************************
# Executable programs

sudokuChecker: sudokuChecker.o
	$(CC) $(CFLAGS) -o sudokuChecker sudokuChecker.o
