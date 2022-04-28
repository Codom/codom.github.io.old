/*
 * wasm_main.c
 * Copyright (C) 2022 Christopher Odom <christopher.r.odom@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/*
 * This is my little playground for wasm stuff. There's no real point
 * other than to just have fun :^)
 */

#include <stdio.h>
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
int w = 500, h = 500;

int offset = 0;

// Some EM_JS hacks
EM_JS(int, canvas_get_width, (), {
    return canvas.width;
})

EM_JS(int, canvas_get_height, (), {
  return canvas.height;
})

EM_JS(int, canvas_resize, (), {
   // look up the size the canvas is being displayed
   const width = canvas.clientWidth;
   const height = canvas.clientHeight;

   // If it's resolution does not match change it
   if (canvas.width !== width || canvas.height !== height) {
     canvas.width = width/2;
     canvas.height = height/2;
     return true;
   }

   return false;
})

void draw() {
    if(SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    if(canvas_resize()) {
        w = canvas_get_width();
        h = canvas_get_height();

        SDL_SetWindowSize(window, w, h);
        SDL_FreeSurface(surface);
        surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    }

    for(int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j) {
#ifdef TEST_SDL_LOCK_OPTS
            int alpha = 255;
#else
            int alpha = i+j % 255;
#endif
            int out_i = (i + offset) % w;
            int out_j = (j + offset) % h;
            *((Uint32*)surface->pixels + out_i * h + out_j) = SDL_MapRGBA(surface->format, i%256, j%256, (255-i)%256, alpha);
        }
    }

    offset+=2;

    if(SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    SDL_Texture *surface_tex = SDL_CreateTextureFromSurface(renderer, surface);
    if(!surface_tex) {
        emscripten_log(EM_LOG_ERROR, "Couldn't make texture!");
        return;
    }

    SDL_Rect rect = {0,0,10,10};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, surface_tex, NULL, NULL);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(surface_tex);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    w = canvas_get_width();
    h = canvas_get_height();
    SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
    if(!renderer) {
        return 1;
    }

    surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if(!surface) {
        emscripten_log(EM_LOG_ERROR, "Couldn't make surface!");
        return 1;
    }

    emscripten_set_main_loop(draw, -1, 1);
}
