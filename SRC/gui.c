#include <gui.h>
/*


void set_pixel(int x, int y, SDL_Surface* surface)
{
    uint8_t *p = (uint8_t *)surface->pixels + y * surface->pitch + x * 4;
    *(uint8_t *)p = 0x0001;
}

GUI* initialize_gui() {

	GUI* gui = malloc(sizeof(GUI));

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf( "SDL_Init Error: %s\n", SDL_GetError());
		exit(-1);
	}

	gui->window = SDL_CreateWindow("VECTOR COMPUTING MACHINE", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	if (gui->window == NULL){
		printf( "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	gui->screen = SDL_GetWindowSurface(gui->window);
	gui->event = malloc(sizeof(SDL_Event));

	return gui;

}
*/