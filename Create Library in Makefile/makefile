OBJS = math_lib.o mathlib.o useLib.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -W $(DEBUG)

#prog : $(OBJS)
	#$(CC) $(OBJS) -o prog
	#will not use this because we try the "library way"
	
prog : useLib.o math_lib.o mathlib.o libmath.a	
	#$(CC) useLib.o -o prog  // This one gives error "in function main undefined reference to `add'"
	$(CC) useLib.o -L. -lmath -o prog

useLib.o : math_lib.c mathlib.h useLib.c
	$(CC) $(CFLAGS) useLib.c
	
mathlib.o : math_lib.c mathlib.h
	$(CC) $(CFLAGS) math_lib.c

libmath.a : math_lib.c mathlib.h
	ar rc libmath.a math_lib.o




	
