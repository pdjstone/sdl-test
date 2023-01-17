#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdlib.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;

int button = 0;
int quit = 0;

void draw() {
    Uint32 colour = 0;
    Uint32 t1 = SDL_GetTicks();
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            button = 1;
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            button = 0;
        } else if (e.type == SDL_QUIT) {
                quit = 1;
        }
    }

    const uint8_t *state = SDL_GetKeyboardState(NULL);

    if (button == 1) 
        colour = 0xff0000;
    else if (state[SDL_SCANCODE_SPACE]) {
        colour = 0xff00ff;
    }

    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);   
    SDL_FillRect(surface, NULL, colour);
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(screenTexture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 512, 0, &window, &renderer);
    surface = SDL_CreateRGBSurface(0, 640, 512, 32, 0, 0, 0, 0);
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(draw, 0, 1);
    #else
    while (quit == 0) { 
        draw(); 
        SDL_Delay(16); 
    }
    #endif
}