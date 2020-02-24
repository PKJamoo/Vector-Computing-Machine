#include <hardware.h>


/* GPU  */ 

gpu* initialize_gpu(mem* mem) {
	gpu* gpu = malloc(sizeof(gpu));


	gpu->vram = mem->VRAM;
	gpu->video_mode = 0;

	return gpu;
}

