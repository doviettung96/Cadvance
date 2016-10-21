#declare the variable
CC=gcc
FLAGS =-g -Wall
CFLAGS=-c $(FLAG)
SRCS=test_lib.c graph.c
OBJS= $(SRCS:.c=.o)
TARGETS= test_lib


#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

#action
all: $(TARGETS) $(SRCS) 
$(TARGETS): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGETS) $(OBJS)
.c.o: 
	$(CC) $(CFLAGS)  $<  -o $@
clean: 
	rm -f core $(OBJS)  $(TARGETS)