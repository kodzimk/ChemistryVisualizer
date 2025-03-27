#include"element.h"

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

void init_atoms(Element* element, int atom_x, int atom_y, int radious, SDL_Color color, int linkedAtom_count)
{
    element->color = color;
    element->protons_size = linkedAtom_count;
    element->x = atom_x;
    element->y = atom_y;
    element->radious = radious;

    int x = atom_x;
    int y = atom_y + radious + radious / 2;
    for (size_t i = 0; i < element->protons_size; i++)
    {
        SDL_Color color = { 255,0,255,255 };
        element->protons[i].x = x;
        element->protons[i].y = y;
        element->protons[i].color = color;
        element->protons[i].radious = radious / 2;
    }
}

void draw_atoms(Element* element, SDL_Renderer* render)
{
    SDL_SetRenderDrawColor(render, element->color.r, element->color.g,
                                   element->color.b, element->color.a);
    render_circle(render, element->x, element->y, element->radious);

    for (size_t i = 0; i < element->protons_size; ++i)
    {
        SDL_SetRenderDrawColor(render, element->protons[i].color.r, element->protons[i].color.g,
                                       element->protons[i].color.b, element->protons[i].color.a);
        render_circle(render, element->protons[i].x, element->protons[i].y, element->protons[i].radious);
    }
}
