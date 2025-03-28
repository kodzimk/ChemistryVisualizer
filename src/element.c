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

void init_atoms(Element* element, int atom_x, int atom_y, int radious, SDL_Color color, int linkedAtom_count, Atom_Type type)
{
    element->color = color;
    element->atom_type = type;
    element->x = atom_x;
    element->proton_count = linkedAtom_count;
    element->y = atom_y;
    element->radious = radious;

    int x = atom_x;
    int y = atom_y;

    int offsetx, offsety, d = 0;
    int proton = 0;

    int index = 0;
    for (size_t i = 0; i < linkedAtom_count; i++)
    {
        if (i >= proton) {
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
            index = 0;
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
            if (element->orbits_size == 2)
                y = atom_y + offsety / 2;
            else
                y = atom_y + offsety / 3;
            x = atom_x - offsetx + radious / 3;
            d = 5;
        }
        else if (d == 5) {
           if(element->orbits_size == 2)
               y = atom_y + offsety / 2;
            else
                y = atom_y + offsety / 3;

            x = atom_x + offsetx - radious / 3;
            d = 6;
        }
        else if (d == 6) {
            if (element->orbits_size == 2)
                y = atom_y - offsety / 2;
            else
                y = atom_y - offsety / 3;

            x = atom_x + offsetx - radious / 3;
            d = 7;
        }
        else if (d == 7) {
            if (element->orbits_size == 2)
                y = atom_y - offsety / 2;
            else
                y = atom_y - offsety / 3;
            x = atom_x - offsetx + radious / 3;
            d = 0;
        }

       element->orbits[element->orbits_size - 1].protons[index].color = color;
       element->orbits[element->orbits_size - 1].protons[index].x = x;
       element->orbits[element->orbits_size - 1].protons[index].y = y;
       element->orbits[element->orbits_size - 1].protons[index].radious = radious / 3;
       element->orbits[element->orbits_size - 1].protons_size += 1;
       index++;
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
        for (size_t j = 0; j < element->orbits[i].protons_size; ++j)
        {    
            SDL_SetRenderDrawColor(render, element->orbits[i].protons[j].color.r, element->orbits[i].protons[j].color.g,
                                           element->orbits[i].protons[j].color.b, element->orbits[i].protons[j].color.a);
            render_circle(render, element->orbits[i].protons[j].x, element->orbits[i].protons[j].y, element->orbits[i].protons[j].radious);
        }
    }
}
