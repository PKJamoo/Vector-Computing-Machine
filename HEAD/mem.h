#ifndef MEM_H_
#define MEM_H_

#include <util.h>


typedef struct struct_mem mem;
/* Constants for the Memory and Mem Management */
# define MEM_SIZE 65536
# define CACHE_SIZE 128


/* Structs for Memory */
struct struct_mem {

	unsigned char* RAM; // RAM for progams, data, etc
	unsigned char* VRAM; // VRAM for graphics
	unsigned char* CACHE; // cache for fast access
	unsigned char* VREGS; // VREGS, for interaction between CPU and GPU
	unsigned char* IOPORT; // Port for I/O operations, save, load, etc.
	unsigned char* KBDSTS; // check to see if keyboard is used
	unsigned char* KBDDTA; //location where keyboard pressed is stored
	unsigned char* INTRPTR; // memory locations for all interrupt pointer methods.
	unsigned char* BIOS; // BIOS program pointer
	unsigned char* SYS; // system calls

};

/* Function Prototypes for the Memory Manager  */
mem* initialize_memory();
int load_program(void* file_ptr);


/*
MEM MAP
0 - 2:
JMP TO BIOS
3 - 130
PAGE ZERO CACHE
REGS (VREGS, KBD)
INTERRUPT POINTERS,
BIOS
KERNALS

*/


#endif // MEM_H_

