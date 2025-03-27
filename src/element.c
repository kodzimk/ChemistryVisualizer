#include"element.h"
#include<stdbool.h>

int render_circle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
int draw_orbits(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void init_atoms(Element* element, int atom_x, int atom_y, int radious, SDL_Color color, int linkedAtom_count)
{
    element->color = color;
    element->protons_size = linkedAtom_count;
    element->x = atom_x;
    element->y = atom_y;
    element->radious = radious;

    int x = atom_x;
    int y = atom_y - radious -  radious / 1.5;

    int offsetx, offsety, d = 0;
    int proton = 0;

    for (size_t i = 0; i < element->protons_size; i++)
    {
        if (i == 0 || i >= proton) {
            element->orbits[element->orbits_size].x = element->x;
            element->orbits[element->orbits_size].y = element->y;

            if (element->orbits_size > 0)
                element->orbits[element->orbits_size].radious = element->radious + element->orbits[element->orbits_size - 1].radious;
            else
                element->orbits[element->orbits_size].radious = element->radious + radious / 1.5;

            element->orbits_size++;
            offsetx = element->orbits[element->orbits_size - 1].radious;
            offsety = element->orbits[element->orbits_size - 1].radious;

            if (i == 0)
                proton += 2;
            else
                proton += 8;

            d = 0;
        }

        if (d == 0) {
            x = atom_x;
            y = atom_y + offsety;
            d = 2;
        }
        else if (d == 2) {
            x = atom_x;
            y = atom_y - offsety;
            d = 1;
        }
        else if (d == 1) {
            y = atom_y;
            x = atom_x + offsety;
            d = 3;
        }
        else if (d == 3) {
            y = atom_y;
            x = atom_x - offsetx;
            d = 4;
        }
        else if (d == 4) {
            y = atom_y + offsety / 2;
            x = atom_x - offsetx + radious / 3;
            d = 5;
        }
        else if (d == 5) {
            y = atom_y + offsety / 2;
            x = atom_x + offsetx - radious / 3;
            d = 6;
        }
        else if (d == 6) {
            y = atom_y - offsety / 2;
            x = atom_x + offsetx - radious / 3;
            d = 7;
        }
        else if (d == 7) {
            y = atom_y - offsety / 2 ;
            x = atom_x - offsetx + radious / 3;
            d = 0;
        }

        element->protons[i].color = color;
        element->protons[i].x = x;
        element->protons[i].y = y;
        element->protons[i].radious = radious / 3;
    }
}

void draw_atoms(Element* element, SDL_Renderer* render)
{
    SDL_SetRenderDrawColor(render, element->color.r, element->color.g,
                                   element->color.b, element->color.a);
    render_circle(render, element->x, element->y, element->radious);

    for (size_t i = 0; i < element->orbits_size; ++i)
    {
        SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
        draw_orbits(render, element->orbits[i].x, element->orbits[i].y, element->orbits[i].radious);
    }

    for (size_t i = 0; i < element->protons_size; ++i)
    {
        SDL_SetRenderDrawColor(render, element->protons[i].color.r, element->protons[i].color.g,
                                       element->protons[i].color.b, element->protons[i].color.a);
        render_circle(render, element->protons[i].x, element->protons[i].y, element->protons[i].radious);
    }
}
