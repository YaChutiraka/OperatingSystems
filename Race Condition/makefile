# Name: (Ya) Naweeya Chutiraka
# UFID: 4663-3911
# Gator ID: nc10nchu

GCC=cc # this an example of a use of Macro
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)

# name the executable anything. I use the same name as its original here

all: increment consecutive spawn

increment.o: increment.c
	$(GCC) $(CFLAGS) increment.c -c

increment: increment.o
	$(GCC) increment.o -o increment
	
consecutive.o: consecutive.c
	$(GCC) $(CFLAGS) consecutive.c -c
	
consecutive: consecutive.o
	$(GCC) consecutive.o  -o consecutive
	
spawn.o: spawn.c
	$(GCC) $(CFLAGS) spawn.c -c
	
spawn: spawn.o
	$(GCC) spawn.o -o spawn
	
clean:
	rm -f increment consecutive spawn *.o

tarfile.tar:
	tar cvf Chutiraka_Ex3.tar Makefile report.txt consecutive.c spawn.c increment.c foo.txt bar.txt
