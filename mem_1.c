/**
 * This code does the first task which is as follows:
 * a) allocating a massive array with malloc and initializing it
 * 
 **/
#include <stdlib.h>
#include <stdio.h>
#include "memlayout.h"

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
	int size = 22; // Size of the regions
	// Memory regions for the first and the second
	struct memregion *memList = malloc(size * sizeof(struct memregion) );	
	struct memregion *memList2 = malloc(size * sizeof(struct memregion) );

	// Doing the first scan
	printf("Doing the first scan:\n");
	printf("There are %d regions.\n", get_mem_layout(memList, size));
	printRegions(memList, size);

	// Allocating a big integer array
	int *intArray = malloc(8192 * sizeof(int));
	for(int i = 0; i < 8192; i++){
		intArray[0]=50;
	}

	// Second scan in between
	printf("Doing the second scan:\n");
	printf("There are %d regions.\n", get_mem_layout(memList2, size));
	printRegions(memList2, size);

	printf("Location of big array: %p", intArray);

	// Deallocate regions
	// free(memList);
	return 0;
}
