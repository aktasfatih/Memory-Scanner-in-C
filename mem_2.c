/**
 * This code does the first task which is as follows:
 * a) allocating a massive array with malloc and initializing it
 * 
 **/
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>

// Defining the variables
#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2

struct memregion {
 void *from;
 void *to;
 unsigned char mode; /* MEM_RW, or MEM_RO, or MEM_NO */
};

extern int get_mem_layout (struct memregion *regions, unsigned int size);


/**
 * Prints out the memory regions found.
 **/
void printRegions(struct memregion *memList, unsigned int size){
    for(int i = 0; i < size; i++){
		printf("0x%08x - ", (int)memList[i].from);
		printf("0x%08x ", (int)memList[i].to);
		switch(memList[i].mode){
			case MEM_NO:
				printf("NO\n");
				break;
			case MEM_RO:
				printf("RO\n");
				break;
			case MEM_RW:
				printf("RW\n");
				break;
		}
	}
	printf("\n");
}

int main()
{
	int err;
	int size = 22; // Size of the regions
	// Memory regions for the first and the second
	struct memregion *memList = malloc(size * sizeof(struct memregion) );	
	struct memregion *memList2 = malloc(size * sizeof(struct memregion) );

	// Doing the first scan
	printf("Doing the first scan:\n");
	printf("There are %d regions.\n", get_mem_layout(memList, size));
	printRegions(memList, size);

	// Using mmap

	// Opening the file, creates if not exists
	const char *filepath = "bigfile.txt";
	int fd = open(filepath, O_RDWR | O_CREAT , S_IRUSR | S_IWUSR);
	if(fd == -1){
        printf("\n\"%s \" exists.\n", filepath);
        exit(1);
    }else{
		// Writes to the file to make a big file.
		
		for(int i = 0; i < 0x3000; i++){
			err = write(fd, "hello there\n", 12);
			if(err < 0){
				printf("\n\"%s \" could not be created.\n",
					filepath);
				exit(1);
			}

		}
	}

	struct stat statbuf;
    err = fstat(fd, &statbuf);
    if(err < 0){
        printf("\n\"%s \" could not open\n", filepath);
        exit(2);
    }

	char *ptr = mmap(
			NULL,
			statbuf.st_size,
            PROT_READ|PROT_WRITE, 
			MAP_SHARED,
            fd, 0);
    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
    }
    close(fd);

	// Second scan in between
	printf("Doing the second scan:\n");
	printf("There are %d regions.\n", get_mem_layout(memList2, size));
	printRegions(memList2, size);

	printf("Location of big file mmap: %p\n", ptr);

	// Unmapping the file
	err = munmap(ptr, statbuf.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }

	// Deallocate regions
	// free(memList);
	return 0;
}
