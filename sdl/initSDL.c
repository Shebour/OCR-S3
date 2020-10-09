#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"

void init(){
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}

SDL_Surface *loadImage(char *path){
    SDL_Surface *image;
    image = SDL_LoadBMP(path);
    if (!image)
        errx(3, "Can't load %s : %s", path, IMG_GetError());
    return image;
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;
    }
}

void setPixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel){

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch
        + x * surface->format->BytesPerPixel;
    switch(surface->format->BytesPerPixel){
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else{
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void displayPicture(SDL_Surface *picture){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    init(); 
    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, picture->w, picture->h, 0);
    if (window == NULL)
        errx(1, "Could not init the window : %s", SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(picture);
    SDL_Quit();
}

Uint8 maxValue(Uint8 r, Uint8 g, Uint8 b){
    Uint8 max = r;
    if (g < b && b > r)
        max = b;
    if (g > b && g > r)
        max = g;
    return max;
}

void greyScale(SDL_Surface *picture){
    Uint32 pixel;
    for (int i = 0; i < picture->w; i++){
        for (int j = 0; j < picture->h; j++){
            Uint8 r, g, b;
            pixel = getPixel(picture, i, j);
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            int average = 0.3 * r + 0.59 * g + 0.11 * b;
            r = b = g = average;
            pixel = SDL_MapRGB(picture->format, r, g, b);
            setPixel(picture, i, j, pixel);
        }
    }
}

void waitForKbEvent(){
    if (NULL == SDL_KeyboardEvent(SDL_KEYDOWN, 5, SDL_PRESSED, SDL_KEYSYM(SDL_SCANCODE_G)))
        printf("Please, press the G key to run");
}

int main(){
    SDL_Surface *picture;
    picture = IMG_Load("test2.bmp");
    if (picture == NULL)
        errx(1, "Could not open the picture : %s", SDL_GetError());
    waitForKbEvent();
    greyScale(picture);
    displayPicture(picture);
    return 0;
}
