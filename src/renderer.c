#include"renderer.h"
#define MY_FONT "/res/font.ttf"

void init_renderer(Renderer* render)
{
    render->run = 1;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    render->window = SDL_CreateWindow("ChemistryVisualizer", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (render->window == NULL) {
        fprintf(stderr, "SDL could not create window! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    render->renderer = SDL_CreateRenderer(render->window, -1, SDL_RENDERER_SOFTWARE);
    if (render->renderer == NULL) {
        fprintf(stderr, "SDL could not create window! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    init_atoms(&render->firstElement, 80, 200, 15, (SDL_Color){.r = 255,.g = 0, .b = 0,.a = 255},8,IRON);
    init_atoms(&render->secondElement, 250, 200, 15, (SDL_Color) { .r = 0, .g = 255, .b = 0, .a = 255 },20,NONE_IRON);
}

void update_renderer(Renderer* render)
{
    SDL_Rect startButton = { 150,350,100,50 };
    bool renderResult = 0;
    while (render->run) {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {

                }
            }
            else if (event.type == SDL_QUIT) {
                render->run = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y = 0;
                SDL_GetMouseState(&x, &y);
                if (x > 50 && x < 250 && y > 350 && y < 400) {
                    renderResult = true;
                    add_atom_to_tom(render);
                }
            }
        }


        SDL_SetRenderDrawColor(render->renderer, 0, 0, 255, 255);
        SDL_RenderClear(render->renderer);

        draw_atoms(&render->firstElement, render->renderer);
        draw_atoms(&render->secondElement, render->renderer);

        if (renderResult)
        {
            draw_atoms(&render->mainAtom, render->renderer);
            draw_atoms(&render->linkedAtom, render->renderer);
        }

        SDL_SetRenderDrawColor(render->renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(render->renderer, &startButton);

        SDL_RenderPresent(render->renderer);
    }
    
}

void end_section(Renderer* render)
{
    SDL_DestroyRenderer(render->renderer);
    SDL_DestroyWindow(render->window);
    SDL_Quit();
}

void add_atom_to_tom(Renderer* render)
{
    int firstProtonCount = 8 - render->firstElement.orbits[render->firstElement.orbits_size - 1].protons_size;
    int secondProtonCount = 8 - render->secondElement.orbits[render->secondElement.orbits_size - 1].protons_size;
    
    if (firstProtonCount > secondProtonCount && firstProtonCount + secondProtonCount == 8 
        && render->firstElement.atom_type == NONE_IRON && render->secondElement.atom_type == IRON)
    {
        init_atoms(&render->mainAtom, render->secondElement.x + 150, render->secondElement.y, 15,
            (SDL_Color) {
            .r = 255, .g = 0, .b = 0, .a = 255
        }, render->firstElement.proton_count + secondProtonCount, NONE_IRON);
        init_atoms(&render->linkedAtom, render->mainAtom.x + 150, render->firstElement.y, 15,
            (SDL_Color) {
            .r = 255, .g = 255, .b = 0, .a = 255
        }, render->secondElement.proton_count - secondProtonCount, IRON);
    }
    else if(firstProtonCount < secondProtonCount && firstProtonCount + secondProtonCount == 8
        && render->firstElement.atom_type == IRON && render->secondElement.atom_type == NONE_IRON) {
        init_atoms(&render->mainAtom, render->secondElement.x + 150, render->secondElement.y, 15,
            (SDL_Color) {
            .r = 255, .g = 0, .b = 0, .a = 255
        }, render->firstElement.proton_count + firstProtonCount, NONE_IRON);
        init_atoms(&render->linkedAtom, render->mainAtom.x + 150, render->firstElement.y, 15,
            (SDL_Color) {
            .r = 255, .g = 255, .b = 0, .a = 255
        }, render->secondElement.proton_count - firstProtonCount, IRON);
    }
    else {
        fprintf(stderr, "Incorrect to add!\n");
        exit(1);
    }
}

