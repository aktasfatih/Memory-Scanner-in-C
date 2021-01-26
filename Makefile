CC=gcc

CFLAGS= -Wall  -g -m32 

# Adding the custom page size
CFLAGS+=-DUSER_PAGE_SIZE=16384

all: memlayout.o mem_1.o

mem_1.o: mem_1.c memlayout.o
	$(CC) $(CFLAGS) mem_1.c memlayout.o -o mem_1.o

memlayout.o: memlayout.c memlayout.h
	$(CC) $(CFLAGS) -c memlayout.c 

clean:
	rm -rf *.o result*




