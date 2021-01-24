CC=gcc
# -m32
CFLAGS= -Wall  -g -m32

all: memlayout.c memlayout.h
	$(CC) $(CFLAGS) memlayout.c -o run

clean:
	rm -rf *.o 




