#include"renderer.h"
#define RENDERER_H

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
}

void update_renderer(Renderer* render)
{
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
        }
        SDL_SetRenderDrawColor(render->renderer, 0, 0, 255, 255);
        SDL_RenderClear(render->renderer);
        SDL_RenderPresent(render->renderer);
    }
    
}

void end_section(Renderer* render)
{
    SDL_DestroyRenderer(render->renderer);
    SDL_DestroyWindow(render->window);
    SDL_Quit();
}

