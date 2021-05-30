#include "hardware.h"
#include "gui.h"
#include "shell.h"


comp* initialize_VCM(){


	comp* comp = malloc(sizeof(comp));
	
	// initialize memory
	mem* mem = initialize_memory();
	comp->mem = malloc(sizeof(mem));

	// intialize cpu
	cpu* cpu = initialize_cpu(mem);
	comp->cpu = malloc(sizeof(cpu));

	// initialize gpu
	gpu* gpu = initialize_gpu(mem);
	comp->gpu = malloc(sizeof(gpu));

	return comp;
}


int main(void) 
{

	// initialize hardware
	unsigned char mainmem[MEM_SIZE];
	processor = malloc(sizeof(cpu));
	graphics = malloc(sizeof(gpu));

	
	shell();

	printf("halt: processor stopped\n");

}

