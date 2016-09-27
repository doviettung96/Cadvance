all: test sort
test: test.o symboltab.o
	gcc -o test test.o symboltab.o
sort: sort.o gen.o
	gcc -o sort sort.o gen.o
sort.o: sort.c
	gcc -c sort.c
gen.o: gen.c
	gcc -c gen.c
test.o: test.c
	gcc -c test.c
symboltab.o: symboltab.c
	gcc -c symboltab.c