#ifndef ELEMENT_H
#define ELEMENT_H

#include<SDL.h>

typedef struct {
	int x;
	int y;
	int radious;
	SDL_Color color;
}Proton;

typedef struct {
	int x;
	int y;
	int radious;
	SDL_Color color;

	Proton protons[118];
	int protons_size;
}Element;

void init_atoms(Element* element,int atom_x,int atom_y, int radious, SDL_Color color,int linkedAtom_count);
int render_circle(SDL_Renderer* renderer, int x, int y, int radius);
void draw_atoms(Element* element, SDL_Renderer* render);

#endif //ELEMENT_H

