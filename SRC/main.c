#include <SDL2/SDL.h>
#include "hardware.h"
#include "gui.h"


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
	// initialize GUI
	GUI* gui = initialize_gui();

	// intialize VCM
	comp* comp = initialize_VCM();

	// begin loop
	int quit_flag = 0;


	//SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, 640, 480, 8, 0, 0, 0, 0);
	//SDL_LockSurface( temp_surface );
	//set_pixel(150, 150, temp_surface);
	//SDL_UnlockSurface( temp_surface );
	//SDL_BlitSurface(temp_surface, NULL, gui->screen, NULL);
	//SDL_UpdateWindowSurface( gui->window );

	while (!quit_flag) {
		// check event
		if( SDL_PollEvent(gui->event) != false ) {
            //Click the quit button
            if( gui->event->type == SDL_QUIT ) {
                quit_flag = true;
            }
            // I/O stuff
		}

		// VCM cycles
	}

	// Deallocate temp_surface
	//SDL_FreeSurface( temp_surface );
	//temp_surface = NULL;

	//free (gui->event);
	//gui->event = NULL;

	//Deallocate surface
    //SDL_FreeSurface( gui->screen );
    //gui->screen = NULL;

    //Destroy window
    //SDL_DestroyWindow( gui->window );
    //gui->window = NULL;

    //Quit SDL subsystems
    //SDL_Quit();
	
	return 0;

}

