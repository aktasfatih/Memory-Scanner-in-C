// Memlayout header
#ifndef MEM_LAYOUT
#define MEM_LAYOUT

// Setting up PAGE_SIZE
#ifndef USER_PAGE_SIZE
// #define PAGE_SIZE 4906
const unsigned int PAGE_SIZE = 4096;
#else
// #define PAGE_SIZE USER_PAGE_SIZE
const unsigned int PAGE_SIZE = USER_PAGE_SIZE;
#endif

#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2

struct memregion {
 void *from;
 void *to;
 unsigned char mode; /* MEM_RW, or MEM_RO, or MEM_NO */
};

int get_mem_layout (struct memregion *regions, unsigned int size);

#endif



