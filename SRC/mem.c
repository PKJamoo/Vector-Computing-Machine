#include <mem.h>

/* Memory Manager */ 


/* Structs for Memory 
struct struct_mem {

	char* RAM; // RAM for progams, data, etc
	char* VRAM; // VRAM for graphics
	char* CACHE; // cache for fast access, first slot after the jump.
	char* VREGS; // VREGS, for interaction between CPU and GPU
	char* IOPORT; // Port for I/O operations, save, load, etc.
	char* KBDSTS; // check to see if keyboard is used
	char* KBDDTA; //location where keyboard pressed is stored
	char* INTRPTR; // memory locations for all interrupt pointer methods.
	char* BIOS; // BIOS program pointer
	char* SYS; // system calls



};
*/

mem* initialize_memory() 
{
	mem* mem = malloc(sizeof(mem));
	// RAM STUFF
	mem->RAM = malloc(sizeof(unsigned char) * (MEM_SIZE));

	// cache begins on byte #4, after the jmp to BIOS
	mem->CACHE = &mem->RAM[3];

	mem->VREGS = malloc(sizeof(unsigned char) * (MEM_SIZE));
	//mem->IOPORT;
	//mem->KBDSTS;
	//mem->KBDDTA;
	//mem->INTRPTR;


	mem->VRAM = malloc(sizeof(unsigned char) * (MEM_SIZE));
	// ROM STUFF
	//mem->BIOS;
	//mem->SYS;

	return mem;
}


void free_memory(mem* mem) 
{
	free(mem->RAM);
	free(mem->VRAM);
	free(mem);
	mem = NULL;

}

