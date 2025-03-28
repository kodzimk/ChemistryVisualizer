#ifndef RENDERER_H
#define RENDERER_H

#include<stdbool.h>
#include<stdio.h>

#include"element.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct{
	bool run;
	Element firstElement;
	Element secondElement;
	Element mainAtom;
	Element linkedAtom;
	SDL_Window* window;
	SDL_Renderer* renderer;
}Renderer;

void init_renderer(Renderer* render);
void update_renderer(Renderer* render);
void add_atom_to_tom(Renderer* render);
void end_section(Renderer* render);

#endif //RENDERER_H