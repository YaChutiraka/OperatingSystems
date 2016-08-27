GCC=gcc # this an example of a use of Macro

# name the executable anything. It is helloWorld here
helloWorld: bar.o main.o
	$(GCC) bar.o main.o -o helloWorld

bar.o: bar.c bar.h
	$(GCC) -c bar.c
	
main.o: main.c bar.h
	$(GCC) -c main.c

clean:
	rm -f helloWorld *.o

tar:
	tar cfv helloWorld.tar bar.c bar.h main.c

