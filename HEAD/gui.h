#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>

/*
NEEDS:
ALL INPUT/OUTPUT must happen through calls from cpu/gpu
READ INPUT FROM USER : CPU -> GUI -> CPU
UPDATE SCREEN: 		   GPU -> VRAM -> GUI
*/

typedef struct struct_gui GUI;


unsigned char read_input();
GUI* initialize_gui();
void initialize_window(int width, int height);
void close_SDL();
void close_window();
void set_pixel(int x, int y, SDL_Surface* surface);

struct struct_gui {
	SDL_Window* window;
	SDL_Surface* screen;
	SDL_Event* event;
};

#endif // GUI_H
