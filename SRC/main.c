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
	mainmem = initialize_memory();
	processor = initialize_cpu(mainmem);
	reset_cpu(processor);
	graphics = malloc(sizeof(gpu));

	
	shell();

	printf("halt: processor stopped\n");

}

