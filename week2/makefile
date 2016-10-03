all: test sort jtest
test: test.o symboltab.o
	gcc -o test test.o symboltab.o
sort: sort.o gen.o
	gcc -o sort sort.o gen.o
jtest: jtest.o
	gcc -o jtest jtest.o jval.o
jtest.o: jtest.c
	gcc -c jtest.c
jval.o: jval.c
	gcc -c jval.c
sort.o: sort.c
	gcc -c sort.c
gen.o: gen.c
	gcc -c gen.c
test.o: test.c
	gcc -c test.c
symboltab.o: symboltab.c
	gcc -c symboltab.c