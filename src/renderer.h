#ifndef RENDERER_H
#define RENDERER_H

#include<SDL.h>
#include<stdbool.h>
#include<stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct{
	bool run;
	SDL_Window* window;
	SDL_Renderer* renderer;
}Renderer;

void init_renderer(Renderer* render);
void update_renderer(Renderer* render);
void end_section(Renderer* render);

#endif //RENDERER_H