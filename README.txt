By: Fatih Aktas

## How-to-use
1 - You 'make' to compile the c codes.
2 - Run mem_1.o, mem_2.o, mem_3.o
3 - Observe the differences caused in the memory because of 
the selected action.

# Files:
- mem_1.c
- mem_2.c
- mem_3.c
- Makefile
- memlayout.c
- memlayout.h
- README.txt

Note the results below are ran using the CFLAG below to set the PAGE_SIZE.
    CFLAG=-DUSER_PAGE_SIZE=16384

## File: mem_1.c
Action:
This code calls get_mem_layout before and after
allocating a massive array with malloc and initializing it.
Then, it prints out the location of the array and the location
of the last item in that array.

Results: >> ./mem_1.o
    Memory Before(13 Regions):
    0x00000000 - 0x08047fff NO
    0x08048000 - 0x08049fff RO
    0x0804a000 - 0x0804afff RW
    0x0804b000 - 0x09dbffff NO
    0x09dc0000 - 0x09de0fff RW
    0x09de1000 - 0xf7d14fff NO
    0xf7d15000 - 0xf7d15fff RW
    0xf7d16000 - 0xf7ec5fff RO
    0xf7ec6000 - 0xf7ec6fff NO
    0xf7ec7000 - 0xf7ec8fff RO
    0xf7ec9000 - 0xf7eccfff RW
    0xf7ecd000 - 0xf7f22fff NO (0xf7ee2008 is here)
    0xf7f23000 - 0xf7f23fff RW 
    0xf7f24000 - 0xf7f24fff RO
    0xf7f25000 - 0xf7f26fff NO
    0xf7f27000 - 0xf7f4cfff RO
    0xf7f4d000 - 0xf7f4dfff RW
    0xf7f4e000 - 0xff41dfff NO
    0xff41e000 - 0xffc1dfff RW
    0xffc1e000 - 0xffffffff NO
    0x00000000 - 0x00000000 NO
    0x00000000 - 0x00000000 NO

    Memory After(15 Regions):
    0x00000000 - 0x08047fff NO
    0x08048000 - 0x08049fff RO
    0x0804a000 - 0x0804afff RW
    0x0804b000 - 0x09dbffff NO
    0x09dc0000 - 0x09de0fff RW
    0x09de1000 - 0xf7d14fff NO
    0xf7d15000 - 0xf7d15fff RW
    0xf7d16000 - 0xf7ec5fff RO
    0xf7ec6000 - 0xf7ec6fff NO
    0xf7ec7000 - 0xf7ec8fff RO
    0xf7ec9000 - 0xf7eccfff RW
    0xf7ecd000 - 0xf7ee1fff NO
    0xf7ee2000 - 0xf7f23fff RW (0xf7ee2008 is here)
    0xf7f24000 - 0xf7f24fff RO
    0xf7f25000 - 0xf7f26fff NO
    0xf7f27000 - 0xf7f4cfff RO
    0xf7f4d000 - 0xf7f4dfff RW
    0xf7f4e000 - 0xff41dfff NO
    0xff41e000 - 0xffc1dfff RW
    0xffc1e000 - 0xffffffff NO
    0x00000000 - 0x00000000 NO
    0x00000000 - 0x00000000 NO

    Location of big array: 0xf7ee2008
    Location of last element: 0xf7f22004

Differences Before-After:
The permissions of the address space regions
have changed. The location 0xf7ee2008 changed from NO to RW.

Reason behind the differences:
The program allocated a space that was enough for the big array to be stored
in a page starting at 0xf7ee2008. The allocated space needed Read-Write access, So
it made one.

## File: mem_2.c
Action:
This file creates a bigfile.txt file.
Then, it calls get_mem_layout before and after calling mmap() for bigfile.txt.

Results:
    Memory Before: 
    0x00000000 - 0x08047fff NO
    0x08048000 - 0x0804afff RO
    0x0804b000 - 0x0804bfff RW
    0x0804c000 - 0x081e7fff NO
    0x081e8000 - 0x08208fff RW
    0x08209000 - 0xf7ceffff NO
    0xf7cf0000 - 0xf7cf0fff RW
    0xf7cf1000 - 0xf7ea0fff RO
    0xf7ea1000 - 0xf7ea1fff NO
    0xf7ea2000 - 0xf7ea3fff RO
    0xf7ea4000 - 0xf7ea7fff RW
    0xf7ea8000 - 0xf7efdfff NO (0xf7eda000 was here)
    0xf7efe000 - 0xf7efefff RW
    0xf7eff000 - 0xf7efffff RO
    0xf7f00000 - 0xf7f01fff NO
    0xf7f02000 - 0xf7f27fff RO
    0xf7f28000 - 0xf7f28fff RW
    0xf7f29000 - 0xff541fff NO
    0xff542000 - 0xffd41fff RW
    0xffd42000 - 0xffffffff NO
    0x00000000 - 0x00000000 NO
    0x00000000 - 0x00000000 NO
    
    Memory After:
    0x00000000 - 0x08047fff NO
    0x08048000 - 0x0804afff RO
    0x0804b000 - 0x0804bfff RW
    0x0804c000 - 0x081e7fff NO
    0x081e8000 - 0x08208fff RW
    0x08209000 - 0xf7ceffff NO
    0xf7cf0000 - 0xf7cf0fff RW
    0xf7cf1000 - 0xf7ea0fff RO
    0xf7ea1000 - 0xf7ea1fff NO
    0xf7ea2000 - 0xf7ea3fff RO
    0xf7ea4000 - 0xf7ea7fff RW
    0xf7ea8000 - 0xf7ed9fff NO
    0xf7eda000 - 0xf7efefff RW (Location of big file mmap: 0xf7eda000)
    0xf7eff000 - 0xf7efffff RO
    0xf7f00000 - 0xf7f01fff NO
    0xf7f02000 - 0xf7f27fff RO
    0xf7f28000 - 0xf7f28fff RW
    0xf7f29000 - 0xff541fff NO
    0xff542000 - 0xffd41fff RW
    0xffd42000 - 0xffffffff NO
    0x00000000 - 0x00000000 NO
    0x00000000 - 0x00000000 NO

    Location of big file mmap: 
        0xf7eda000

Differences Before-After:
It can be seen that there was no access in 0xf714c000 before the allocation.
It was NO. After the allocation, 0xf7eda000 was a RW location used by the mmap operation in the 
memory. 

Reason behind the differences:
mmap() maps memory address space with a file in this code, which is bigfile.txt.
Since we mapped the file with both read and write access, mmap mapped the file
into address space as much as it needed for the file. So, it caused a change starting
at 0xf714c000 giving it a RW access.

## File: mem_3.c
Action:
This file runs a recursive function that adds integers up to integer i. 
For each integer, it allocates an int in the memory space that is i-1.
Then, it adds those up in a recursive way. 
It prints out the address and the value of the recursive i found in the function.
It then runs get_mem_layout before and after.

Results:
    Memory Before: 
        0x00000000 - 0x08047fff NO
        0x08048000 - 0x08049fff RO
        0x0804a000 - 0x0804afff RW
        0x0804b000 - 0x0852dfff NO
        0x0852e000 - 0x0854efff RW
        0x0854f000 - 0xf7d41fff NO
        0xf7d42000 - 0xf7d42fff RW
        0xf7d43000 - 0xf7ef2fff RO
        0xf7ef3000 - 0xf7ef3fff NO
        0xf7ef4000 - 0xf7ef5fff RO
        0xf7ef6000 - 0xf7ef9fff RW
        0xf7efa000 - 0xf7f4ffff NO
        0xf7f50000 - 0xf7f50fff RW
        0xf7f51000 - 0xf7f51fff RO
        0xf7f52000 - 0xf7f53fff NO
        0xf7f54000 - 0xf7f79fff RO
        0xf7f7a000 - 0xf7f7afff RW
        0xf7f7b000 - 0xff40dfff NO
        0xff40e000 - 0xffc0dfff RW
        0xffc0e000 - 0xffffffff NO
        0x00000000 - 0x00000000 NO
        0x00000000 - 0x00000000 NO

    Memory After:
        0x00000000 - 0x08047fff NO
        0x08048000 - 0x08049fff RO
        0x0804a000 - 0x0804afff RW
        0x0804b000 - 0x0852dfff NO
        0x0852e000 - 0x0854efff RW
        0x0854f000 - 0xf7d41fff NO
        0xf7d42000 - 0xf7d42fff RW
        0xf7d43000 - 0xf7ef2fff RO
        0xf7ef3000 - 0xf7ef3fff NO
        0xf7ef4000 - 0xf7ef5fff RO
        0xf7ef6000 - 0xf7ef9fff RW
        0xf7efa000 - 0xf7f4ffff NO
        0xf7f50000 - 0xf7f50fff RW
        0xf7f51000 - 0xf7f51fff RO
        0xf7f52000 - 0xf7f53fff NO
        0xf7f54000 - 0xf7f79fff RO
        0xf7f7a000 - 0xf7f7afff RW
        0xf7f7b000 - 0xff40dfff NO
        0xff40e000 - 0xffc0dfff RW
        0xffc0e000 - 0xffffffff NO
        0x00000000 - 0x00000000 NO
        0x00000000 - 0x00000000 NO

    Location of recursive parameters:
        Number of recursions: 4097
        First level of recursion is at i:0xffc0d340
        Last level of recursion is at i:0xffbdd310
        Result of recursive addition : 8394753

Differences Before-After:
Allocated memory space for i is in from 0xffc0d340 to 0xffbdd310 is in a RW access
in the memory space, which was NO permission before.


Reason behind the differences:
As the recursiveAddition() function recurses into deeper levels
to calculate, it pushes new rows into the stack. Every new allocated
memory space for i is in from 0xffc0d340 to 0xffbdd310 with a RW access
 in the memory space, which was NO permission before. 
 In C, recursive functions push more elements to the stack as it goes into deeper 
levels of recursion, causing the stack to grow in size. The allocated space
for j, which equals j=i-1 requires space in the memory. So, the result 
ends up in the RW space starting at 0xffc0d340 to be used by recursiveAddition.
