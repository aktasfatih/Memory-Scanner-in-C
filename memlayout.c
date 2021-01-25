#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <signal.h>
#include "memlayout.h"

// Storing the current memory access type
static sig_atomic_t current_access, last_access;

// Storing where to return after the signal handlers
static sigjmp_buf jumpbuf;

// For making sure the process controlling this doesn't get affected.
static struct sigaction oldsignalhandle;

// Signal handler for SIGSEGV
static void handler(int signum) {
	siglongjmp(jumpbuf, 1);
}

// Memory scan function
int get_mem_layout (struct memregion *regions, unsigned int size){

	// Saving the old signal
  	sigaction(SIGSEGV, NULL, &oldsignalhandle);

	// Assigning new signal handler
  	signal(SIGSEGV, handler);
	signal(SIGBUS, handler);

  	int *currentAddress; // This is the current address we are in for the search.
  	int readValue; // This is the value in the currentAddress	
	int pageSize = getpagesize(); // Page size of a memory space
	int listIndex = 0; // The current index in regions
	int isItFirst = 1; // Active in currentAddress = 0x0

	for(
		currentAddress = 0xf0fd5000; // Scan starts at 0x0
		currentAddress <= (0xFFFFFFFF - pageSize) + 1; // It goes until 0xFFFF F000 
		currentAddress += (pageSize >> 2) // It is a int addition to pointer. 
	){
		printf("%p\n", currentAddress);
		current_access = MEM_NO;
        if ( sigsetjmp(jumpbuf, 1 ) == 0 ){
            /* Reading operation */
            readValue = *currentAddress;
            current_access = MEM_RO;	

            /* Writing operation */
            *currentAddress = readValue;
            current_access = MEM_RW;			
        }	

		// Putting the values into the array
		if(isItFirst){
			regions[listIndex].from = currentAddress;
			regions[listIndex].to = (int*)((int)currentAddress + pageSize - 1);
			regions[listIndex].mode = current_access;
			isItFirst = 0;
		}else if(listIndex < size){
				if(current_access != last_access){
					listIndex ++;
					regions[listIndex].from = currentAddress;
					regions[listIndex].to = (int*)((int)currentAddress + pageSize - 1);
					regions[listIndex].mode = current_access;
				}else{
					regions[listIndex].to = (int*)((int)currentAddress + pageSize - 1);
				}
		}

		last_access = current_access;
    }

	// Loading the old signal handler
	sigaction(SIGSEGV, &oldsignalhandle, NULL);
    return 0;
}

int main()
{
	int size = 10;
	struct memregion *mem_list = NULL;

	mem_list = malloc(size * sizeof(struct memregion) );
	
	get_mem_layout(mem_list, size);

	for(int i = 0; i < size; i++){
		printf("0x%x - ", (int)mem_list[i].from);
		printf("0x%x ", (int)mem_list[i].to);
		switch(mem_list[i].mode){
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

	/* Deallocate the memory */
	free(mem_list);
	return 0;
}
