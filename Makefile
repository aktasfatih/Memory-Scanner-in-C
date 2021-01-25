CC=gcc

CFLAGS= -Wall  -g -m32

all: memlayout

memlayout: memlayout.c memlayout.h
	$(CC) $(CFLAGS) memlayout.c -o memlayout


clean:
	rm -rf memlayout result*




