#General makefile to compile all the c files in directory
GCC=gcc
CFLAGS=-Wall -c
SRCS=stack.c


OBJ=${SRCS:.c=.o}

.PHONY: all 
all: clean $(OBJ)

%.o: %.c
	$(GCC) $(CFLAGS) $< -o $@
	cp $@ $(basename $@)

clean:
	rm -rf *.o
