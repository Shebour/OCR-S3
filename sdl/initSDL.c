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

void displayPicture(SDL_Surface *picture){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, picture->w, picture->h, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * listPic[] = {picture, greyScale(picture), blackNWhite(picture)};
    size_t len = 3;
    for (size_t i = 0; i < len; i++){
        texture = SDL_CreateTextureFromSurface(renderer, listPic[i]);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(picture);
}

char waitForKeyPressed(){    
    char key;
    printf("if you want to see the picture after greyScale press G, anything else to skip and see the picture after blackNWhite.");
    if (scanf("%c", &key) == 'g')
        return key;
    else
        return 'a';    
}

void affichage(){
    init();
    SDL_Surface *picture;
    picture = IMG_Load("test2.bmp");    
    if (picture == NULL)
        errx(1, "Could not open the picture : %s", SDL_GetError());
    displayPicture(picture);
}

int main(){
    affichage();
    return 0;
}
