#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"

void init(){
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}

char wait_for_key_pressed(){    
    char key;
    if (scanf("%c", &key) == 'g')
        return key;
    else
        return 'a';    
}

SDL_Surface * load_picture(char *path){ 
    SDL_Surface *picture;
    if (path != NULL)
        picture = IMG_Load(path);
    else
        errx(1, "no path");
    if (picture == NULL)
        errx(1, "Could not open the picture : %s", SDL_GetError()); 
    return picture;
}



void display(SDL_Surface * picture){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    grey_scale(picture);
    black_white(picture);

    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, picture->w, picture->h, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTextureFromSurface(renderer, picture);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000); 
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);

    SDL_FreeSurface(picture);
}

