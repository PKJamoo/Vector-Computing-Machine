#ifndef HARDWARE_H_
#define HARDWARE_H_

/* Hardware Components							   */
#include <mem.h>
#include <gpu.h>
#include <cpu.h>
/*-------------------------------------------------*/


/* Constants for the CPU */

// Typedefs
typedef struct struct_comp comp;

/* Container struct for the whole of the computer */
struct struct_comp {
	cpu* cpu;
	gpu* gpu;
	mem* mem;
};



#endif // HARDWARE_H_
