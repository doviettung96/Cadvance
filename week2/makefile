all: test
test: test.o generictab.o
	gcc -o test test.o generictab.o
test.o: test.c
	gcc -c test.c
generictab.o: generictab.c
	gcc -c generictab.c