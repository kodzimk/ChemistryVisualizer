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

	Proton protons[8];
	int protons_size;
}Orbit;

typedef enum {
	NONE = 0,
	IRON,
	NONE_IRON,
}Atom_Type;

typedef struct {
	int x;
	int y;
	int radious;
	SDL_Color color;

	Orbit orbits[16];
	int orbits_size;

	Atom_Type atom_type;
	int proton_count;
}Element;

void init_atoms(Element* element,int atom_x,int atom_y, int radious, SDL_Color color,int linkedProtromnSAize,Atom_Type type);
int render_circle(SDL_Renderer* renderer, int x, int y, int radius);
void draw_atoms(Element* element, SDL_Renderer* render);

#endif //ELEMENT_H

