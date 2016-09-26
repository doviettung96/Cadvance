all: quicksort
quicksort: sort.o quicksort.o
	gcc -o quicksort quicksort.o sort.o
quicksort.o: quicksort.c
	gcc -c quicksort.c
sort.o: sort.c
	gcc -c sort.c
