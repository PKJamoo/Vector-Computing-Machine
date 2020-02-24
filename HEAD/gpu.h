#ifndef GPU_H_
#define GPU_H_

#include <util.h>

typedef struct struct_gpu gpu;

/* Constants for the GPU */

/* Structs for the GPU */
struct struct_gpu {

	unsigned char* vram;
	uint16_t video_mode;

};


/* Function Prototypes for the GPU */
gpu* initialize_gpu(mem* mem);
void draw_line();
void draw_rect();
void draw_circle();




#endif // GPU_H_
